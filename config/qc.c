#include <stdio.h>
#include <qstring.h>
#include <qcstring.h>

main()
{
	for( int i=128; i<256; i++ ) {
		char buf[4];
		sprintf(buf, "%c", i);

		QString c(buf);
		const char *p = (const char *)c.utf8();
		while( *p )
			printf("%x ", (unsigned char)*p++);
		puts("");
	}
}
