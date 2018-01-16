#include <stdlib.h>
#include <stdio.h>
#include <rpc/rpc.h>

#include "minifyjpeg_xdr.c"
#include "minifyjpeg_clnt.c"
#include <errno.h>

CLIENT* get_minify_client(char *server) {
	CLIENT *cl;
	/* Your code here */
	cl = clnt_create(server, MINIFYJPEG_PROG, MINIFYJPEG_VERS, "tcp");
	if (cl == NULL) {
		clnt_pcreateerror(server);
	}

	struct timeval tv;
	tv.tv_sec = 6; /* change timeout to 1 minute */
	tv.tv_usec = 0; /* this should always be set  */
	clnt_control(cl, CLSET_TIMEOUT, &tv);

	puts("Client created successfully");

	return cl;
}

void* minify_via_rpc(CLIENT *cl, void* src_val, size_t src_len, size_t *dst_len) {
	/*Your code here */
	printf("Start calling rpc with size %ld\n", src_len);
	FileTransfer request;
	FileTransfer* result;
	request.fileHandler.fileHandler_len = src_len;
	request.fileHandler.fileHandler_val = src_val;

	puts("Done creating request");

	result = getfile_1(request, cl);

	puts("Request sent");

	if (result == (FileTransfer *) NULL) {
		printf("Error number is %d\n", errno);
		clnt_perror(cl, "call failed");
		return NULL;
	} else {
		puts("Received");
		*dst_len = result->fileHandler.fileHandler_len;
		return result->fileHandler.fileHandler_val;
	}
}
