# What we need to remember


First we query the `memory` to  check if there is a *buffer object* associated to the `fd`.
```c
t_gnl_buffer *buff;
buff = gnl_query(memory, fd);
```

A buffer object is what is encoded by `t_gnl_buffer`s.
```c
typedef struct s_gnl_buffer
{
	char *data;
	size_t offset;
	size_t length;
} t_gnl_buffer;
```

We have two utility functions to create and delete `s_gnl_buffer`s.

```c
t_gnl_buffer *gnl_create_buffer()
{
	int i;
	t_gnl_buffer *buffer;
	
	i = 0;
	*buffer = (t_ gnl_buffer *)malloc(sizeof(t_gnl_buffer));
	buffer->data = (char *)malloc(BUFFER_SIZE);
	while(i < BUFFER_SIZE)
		(buffer->data)[i++] = 0;
	buffer->offset = 0;
	buffer->length = 0;
	return buffer;
}

void gnl_delete_buffer(t_gnl_buffer *buff)
{
	int i;
	
	i = 0;
	while(i < BUFFER_SIZE)
		(buff->data)[i] = 0;
	free(buffer->data)
	buffer->data = NULL;
	buffer->offset = 0;
	buffer->length = 0;
	free(*buff)
	*buff = NULL;
}
```

The `memory` is a list of key-value pairs, where key are file descriptors and values are pointers pointing to some *buffer object*.

A buffer object is created when we read the file descriptor.

```c
void gnl_read(fd, t_gnl_buffer **buff)
{
	*buff = gnl_create_buffer();
	if (!buff)
		return ;
	(*buff)->length = read(fd, (*buff)->data, BUFFER_SIZE);
}
```

We check if there is something in memory, if not, we read from the fd:

```c
t_gnl_buffer *buff;

buff = gnl_query(fd, memory);
if (buff == NULL)
	gnl_read(fd, &buff);
```

After reading we should check if any `'\n'` char was found:

```c
size_t gnl_get_chunk_length(t_gnl_buffer buff)
{
	size_t cl;//chunk length

	cl = 0;
	while (cl < buff.length - buff.offset && (buff.data)[cl] != '\n')
		cl++;
	return cl;
}
```

```c
void gnl_recursive(int fd, gnl_memory *memory, char **line, size_t ll/*line length*/)
{
	t_gnl_buffer *buff;
	char *buff_data;
	size_t offset;
	size_t length;
	size_t cl;

	buff = gnl_query(fd, memory);//TO DO
	if (buff == NULL)
	{
		gnl_read(fd, &buff);
		if (buff->length <= 0)
			gnl_delete_memory_fd(fd, memory);
		else
			gnl_post(fd, memory, buff);
	}
	buff_data = buff->data;
	buff_offset = buff->offset;
	buff_length = buff->length;
	cl = gnl_get_chunk_length(*buff);//computes chunk length
	ll += cl;// updates line length;
	if (buff->length == buff->offset + cl)
	{
		*line = (char *)malloc(ll+1);
		buff->offset += cl;
	}
	else
	{
		recursive(fd, memory, ll);
		gnl_trash(buff);
	}
	gnl_memory_copy((*line) + (ll - cl), buff_data + buff_offset, cl);
}

char *get_next_line(int fd)
{
	static t_gnl_memory;
	char *line;
	gnl_recursive(fd, &memory, &line, 0);
	return line;
}
```