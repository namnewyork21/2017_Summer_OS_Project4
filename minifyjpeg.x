/*
 * Complete this file and run rpcgen -MN minifyjpeg.x
 */
 
 struct FileTransfer {
	opaque fileHandler<60000000>;
};

program MINIFYJPEG_PROG {
	version MINIFYJPEG_VERS {
	FileTransfer GetFile(FileTransfer) = 1;
} = 1;
} = 0x31234568;
