#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <string>
#include "unistd.h"
#include "Lib/stringutils.h"

#define MAX_LINE_LENGTH    512

using namespace std;
    
int read_line(FILE *fp, char *bp)
{
	char c = '\0';
	int i = 0;
	
	/* Read one line from the source file */
	while((c = getc(fp)) != '\n')
	{
		if(c == EOF)         /* return FALSE on unexpected EOF */
			return 0;
		
		if (c != '\r')  /* Again, MS sucks, ignore CR */
			bp[i++] = c;
	}
	
	bp[i] = '\0';
	
	return 1;
}
   
int get_private_profile_string(const char *section, const char *entry, const char *def, char *buffer, int buffer_len, const char *file_name)
{
	FILE *fp = fopen(file_name,"r");
	char buff[MAX_LINE_LENGTH];
	char *ep;
	char t_section[MAX_LINE_LENGTH];
	// entry == NULL means copy whole section
	int len = (entry != NULL) ? strlen(entry) : 0;
	
	if(!fp) return 0;
		sprintf(t_section,"[%s]",section);    /* Format the section name */
	
	/*  Move through file 1 line at a time until a section is matched or EOF */
	do
	{
		if(!read_line(fp,buff))
		{
			fclose(fp);
			strncpy(buffer,def,buffer_len);
			
			return strlen(buffer);
		}
	}
	while(!StartsWith(buff,t_section));
	
	/* Now that the section has been found, find the entry.
	* Stop searching upon leaving the section's area. */
	do
	{
		if(!read_line(fp,buff) || buff[0] == '[')
		{
			fclose(fp);
			strncpy(buffer,def,buffer_len);
		
			return(strlen(buffer));
		}
	}
	while((len == 0) || strncmp(buff,entry,len));

	if (len > 0)
	{
		ep = strrchr(buff,'=');    /* Parse out the equal sign */
		ep++;
		/* Copy up to buffer_len chars to buffer */
		strncpy(buffer,ep,buffer_len - 1);
	}
	   
	buffer[buffer_len - 1] = '\0';
	fclose(fp);               /* Clean up and return the amount copied */
	
	return strlen(buffer);
}
   
int write_private_profile_string(const char *section, const char *entry, const char *buffer, const char *file_name)
{
	return 0;
}

string GetVar(string File, string Section, string Entry)
{
	char Buffer[1024];
	
	get_private_profile_string(Section.c_str(), Entry.c_str(), "NotFound", Buffer, sizeof(Buffer), File.c_str());
	
	return string(Buffer);
}

int GetVarInt(string File, string Section, string Entry)
{
	char Buffer[1024];
	
	get_private_profile_string(Section.c_str(), Entry.c_str(), "0", Buffer, sizeof(Buffer), File.c_str());
	
	return atoi(string(Buffer).c_str());
}

void SetVar(string File, string Section, string Entry, string Value)
{
	write_private_profile_string(Section.c_str(), Entry.c_str(), Value.c_str(), File.c_str());
}

void SetVarInt(string File, string Section, string Entry, int Value)
{
	SetVar(File, Section, Entry, to_string(Value));
}

