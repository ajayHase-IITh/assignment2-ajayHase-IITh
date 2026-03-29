#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	
	const char* fileName;
	const char* stringToWrite;
	int fd = 0;

	//1.Initialize syslog
	openlog("writer", 0, LOG_USER);

	//2.Inpur argument validation 
	//Expected input: program name, file  and string
	if(argc != 3){
		syslog(LOG_ERR, "Invalid #of argument: Expected 3, got %d", argc);
		fprintf(stderr, "Invalid #of argument: Usage: %s <filename> <string> \n", argv[0]);
		closelog();
		return 1;
	}	

	fileName = argv[1];
	stringToWrite = argv[2];

	syslog(LOG_DEBUG, "Writing %s to %s", stringToWrite, fileName);

	//3.Open file to write string
	fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1){
		syslog(LOG_ERR, "Error while opening %s file:%s", fileName, strerror(errno));
		fprintf(stderr, "Error while opening %s file:%s", fileName, strerror(errno));
		closelog();
		return 1;
	}
	
	//4. Write string to file
	size_t len = strlen(stringToWrite);
	int  byteWritten = write(fd, stringToWrite, len);
	if(byteWritten == -1 ||(size_t)byteWritten != len){
		syslog(LOG_ERR, "Error while writing %s file:%s", fileName, strerror(errno));
		close(fd);
		closelog();
		return 1;
	}

	//5. Close file
	int status = close(fd);
	if(status == -1){
		syslog(LOG_ERR, "Error closing %s file:%s", fileName, strerror(errno));
		closelog();
		return 1;
	}

	closelog();
	return 0;

}
