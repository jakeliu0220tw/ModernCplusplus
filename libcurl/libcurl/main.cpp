#include <stdio.h>
#include <iostream>
#include <curl/curl.h>

#define USER_PWD "user:pwd"
#define FTP_URL "ftp://tmp/tmp.zip"

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, FILE *stream)
{
	return fwrite(buffer, size, nmemb, stream);
}

// simple http-get
void example1()
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.cnn.com");
		res = curl_easy_perform(curl);

		// always cleanup
		curl_easy_cleanup(curl);
	}
}

// download file from ftp
void example2()
{
  CURL *curl;
  CURLcode res;

  // open file handle
  FILE* fhandle = fopen("MyFile.zip", "wb");
  if (!fhandle)
	  return;

  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works! Note that we use an
     * FTP:// URL with standard explicit FTPS. You can also do FTPS:// URLs if
     * you want to do the rarer kind of transfers: implicit.
     */
	curl_easy_setopt(curl, CURLOPT_URL, FTP_URL);
	curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_FTP | CURLPROTO_FTPS);
	curl_easy_setopt(curl, CURLOPT_USERPWD, USER_PWD);

    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
	curl_easy_setopt(curl, CURLOPT_FILE, fhandle);

    res = curl_easy_perform(curl);

    if(CURLE_OK != res) {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }

	/* always cleanup */
	curl_easy_cleanup(curl);
  }

  // close file handle
  if (fhandle)
	  fclose(fhandle);
}

int main()
{
	std::cout << "libcurl example" << std::endl;
	//curl_global_init(CURL_GLOBAL_DEFAULT);

	//example1();
	example2();

	//curl_global_cleanup();
	return 0;
}