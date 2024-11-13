#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// calculate the len                    =======done======
int	calclen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len] != '\0')
		len++;
	return (len);
}

// get a new line                      =====done==========
char *find_newline(char *data, int ch)
{
    int i;

    i = 0;
    if (!data)
        return (NULL);
    while (data[i] != '\0')
    {
        if (data[i] == (char)ch)
            return (&data[i]);
        i++;
    }
    return (NULL);
}

// cut the line (\n) from buffer          ======done======
char    *separate_line(char *data)
{
    char    *line;
    int i;
    int j;

    i = 0;
    if (!data)
        return (NULL);
    while (data[i] != '\n' && data[i] != '\0')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    j = 0;
    while (j < i)
    {
        line[j] = data[j];
        j++;
    }
    if (data[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}


// update the bufer by separating the line ======done======
char    *update_buffer(char *data)
{
    char *remaindata;
    char *new_data;
    int i;
    int datalen;

    i = 0;
    datalen = 0;
    remaindata = find_newline(data, '\n');
    if (remaindata)
        remaindata++;
    datalen = calclen(remaindata);
    if (!datalen)
    {
        free(data);
        return (NULL);
    }
    new_data = malloc(sizeof(char) * (datalen+1));
    if (!new_data)
        return (NULL);
    while (i < datalen)
    {
        new_data[i] = remaindata[i];
        i++;
    }
    new_data[datalen] = '\0';
    free(data);
    return(new_data);
}

// Custom implementation of strdup
char *my_strdup(char *src)
{
    char    *dup;
    int len;
    int i;

    i = 0;
    if (!src)
        return NULL;
    len = calclen(src);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    while (src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[len] = '\0';
    return (dup);
}

// strcopy
void ft_copy(char *dest, const char *src) {
    int i;

    i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// strcat
void ft_strcat(char *dest, const char *src) {
    int dest_len;
    
    dest_len = calclen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}
// read from fd and add data to buffer until \n or end of file 
char    *readfromfd(int fd, char *buffer)
{
    char *buf;
    int readed;
    char *temp;

    buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    readed = read(fd, buf, BUFFER_SIZE);
    while (readed > 0)
    {  
        if (readed == -1)
        {
            free(buf);
            return (NULL);
        }
        buf[readed] = '\0';
        if (!buffer)
        {
            buffer = my_strdup(buf);
        }
        else
        {
            temp = buffer;
            buffer = malloc(calclen(temp) + readed + 1);
            ft_copy(buffer, temp);
            ft_strcat(buffer, buf); // concate the old with new  data
            free(temp);
        }
        if (find_newline(buffer, '\n') )
            break;
        readed = read(fd, buf, BUFFER_SIZE);
    }
    free(buf);
    return (buffer);
}


//main function
char *get_next_line(int fd)
{
    static char *buffer = NULL;
    char *line = NULL;
   
    if (!find_newline(buffer, '\n'))// if there is a new \n
    {
       
        buffer = readfromfd(fd, buffer);
    }
     line = separate_line(buffer);
     buffer = update_buffer(buffer);
    return (line);
}




























#include <stdio.h>
#include <fcntl.h>
int main()
{
    char *s;
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return 1;
    }

   while( (s= get_next_line(fd)))
   {
    printf("%s", s);
   }

    close(fd);
    return 0;
}