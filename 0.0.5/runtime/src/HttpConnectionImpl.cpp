// $Id$
#include "hessian/HttpConnectionImpl.h"
#include "hessian/types.h"

namespace {

// timeout in seconds
const long DEFAULT_TIMEOUT = 30;

// Used to clear stream buffer.
const std::string EMPTY;

class CurlGlobalInitializer
{
public:
    CurlGlobalInitializer ()
    { curl_global_init(CURL_GLOBAL_ALL); }

    ~CurlGlobalInitializer ()
    { curl_global_cleanup(); }

    static void initialize();
};

void
CurlGlobalInitializer::initialize ()
{
    static CurlGlobalInitializer initializer;
}

}//namespace

namespace hessian {

HttpConnectionImpl::HttpConnectionImpl (const std::string& url)
{
    CurlGlobalInitializer::initialize();

    pCurl_ = curl_easy_init();
    if (pCurl_ == 0) {
        throw ConnectionException("curl_easy_init failed");
    }

    // Set URL.
    curl_easy_setopt(pCurl_, CURLOPT_URL, url.c_str());

    pHeaders_ = 0;
    // Set Content-Type: header.
    pHeaders_ = curl_slist_append(
            pHeaders_, "Content-Type: x-application/hessian");
    // Do not send Expect: header.
    pHeaders_ = curl_slist_append(pHeaders_, "Expect:");
    curl_easy_setopt(pCurl_, CURLOPT_HTTPHEADER, pHeaders_);

    // Set callback function to receive response data.
    curl_easy_setopt(pCurl_, CURLOPT_WRITEFUNCTION, writeData);

    // Set timeouts.
    curl_easy_setopt(pCurl_, CURLOPT_CONNECTTIMEOUT, DEFAULT_TIMEOUT);
    curl_easy_setopt(pCurl_, CURLOPT_TIMEOUT, DEFAULT_TIMEOUT);

    // Set error message buffer.
    curl_easy_setopt(pCurl_, CURLOPT_ERRORBUFFER, errorBuffer_);
}

HttpConnectionImpl::~HttpConnectionImpl ()
{
    curl_slist_free_all(pHeaders_);
    curl_easy_cleanup(pCurl_);
}

size_t
HttpConnectionImpl::writeData(
        void* pBuffer, size_t elementSize, size_t nElements, void* pUser)
{
    std::streambuf* pResponse = reinterpret_cast<std::streambuf*>(pUser);
    size_t nBytes = elementSize * nElements;
    pResponse->sputn(static_cast<char*>(pBuffer), nBytes);
    return nBytes;
}

int
HttpConnectionImpl::post (
        const char* pContent, size_t contentSize, std::streambuf* pResponse)
{
    responseBuffer_.str(EMPTY);

    curl_easy_setopt(pCurl_, CURLOPT_POST, 1);
    curl_easy_setopt(pCurl_, CURLOPT_POSTFIELDS, pContent);
    curl_easy_setopt(pCurl_, CURLOPT_POSTFIELDSIZE, contentSize);
    curl_easy_setopt(pCurl_, CURLOPT_WRITEDATA, pResponse);

    if (curl_easy_perform(pCurl_) != CURLE_OK) {
        throw ConnectionException(errorBuffer_);
    }

    long responseCode = -1;
    curl_easy_getinfo(pCurl_, CURLINFO_RESPONSE_CODE, &responseCode);
    return responseCode;
}

std::streambuf*
HttpConnectionImpl::send (const MemoryStreamBuf* pRequest)
{
    int statusCode = post(
            pRequest->str(), pRequest->pcount(), &responseBuffer_);
    if (statusCode != 200) {
        std::ostringstream message;
        message << "HTTP POST returned status code " << statusCode;
        throw ProtocolException(message.str());
    }

    return &responseBuffer_;
}

}//namespace hessian
