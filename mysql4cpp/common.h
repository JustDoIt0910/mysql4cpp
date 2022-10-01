#pragma once

#define BUFSIZE_TINYINT			1
#define BUFSIZE_SMALLINT		2
#define BUFSIZE_MEDIUMINT		3
#define BUFSIZE_INT				4
#define BUFSIZE_BIGINT			8
#define BUFSIZE_FLOAT			4
#define BUFSIZE_DOUBLE			8
#define BUFSIZE_TIME			sizeof(MYSQL_TIME)

struct FieldMeta
{
	string name;
	unsigned long length;
	enum enum_field_types type;

	FieldMeta(const MYSQL_FIELD& field)
	{
		name = string(field.name, field.name_length);
		length = field.length;
		type = field.type;
	}
};
