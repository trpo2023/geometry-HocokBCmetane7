#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define READ_FILE_ERROR -1
#define NO_GEOMETRIC_SHAPE_FOUND_ERROR -2
#define LEFT_PARENTHESIS_ERROR -3
#define RIGHT_PARENTHESIS_ERROR -4
char *(GEOMETRIC_SHAPES[]) = {"circle", "triangle", "polygram"};


void CatchError(const char*, const int, const int, const int);
void PrintError(const int, const char*, const int);
int StringCompare(const char*, const char*, const int, const int);





char *DeleteNewline(const char *string, const int str_len)
{
	char * const string_copy = malloc(str_len);
	for (int i = 0; i < str_len-1; i++)
	{
		string_copy[i] = string[i];
	}
	string_copy[str_len-1] = '\0';
	
	return string_copy;
}


int StringCompare(const char * string, const char *geometric_shape, const int str_len, const int geometric_shape_length)
{
	const int geometric_shape_legth = strlen(geometric_shape);
	bool string_match = true;
	for (int i = 0; i < geometric_shape_legth; i++)
	{
		if (string[i] != geometric_shape[i])
		{
			string_match = false;
			break;
		}
	}
	return string_match;
}


void PrintError(const int code_error, const char* string, const int line_number)
{
	switch (code_error)
	{
	case READ_FILE_ERROR:
		printf("%s", "Unsuccesful File input.");
		break;
	case NO_GEOMETRIC_SHAPE_FOUND_ERROR:
		printf("%s %d: %s\n\n%s\n\n\n", "Error in line", line_number, string,"Expected 'circle', 'triangle' or 'polygon'"); //доделать вывод столбца
		break;
	case LEFT_PARENTHESIS_ERROR:
		printf("%s %d: %s\n\n%s\n\n\n", "Error in line",	line_number, string, "Expected '('");
		break;
	case RIGHT_PARENTHESIS_ERROR:
		printf("%s %d: %s\n\n%s\n\n\n", "Error in line",	line_number, string, "expected ')'");
		break;
	default:
	printf("%s", "Unknown error.");
		break;
	}
	
}


void CatchError(const char* string, const int geometric_shapes_arr_size, const int str_len, const int line_number)
{
	int i = 0;
	bool shape_match = false;
	int geometric_shape_length = strlen(GEOMETRIC_SHAPES[i]);
	while(i < geometric_shapes_arr_size)
	{
		shape_match = StringCompare(string, GEOMETRIC_SHAPES[i], str_len, geometric_shape_length); 
		if (shape_match)
		{
			shape_match = true;
			geometric_shape_length = strlen(GEOMETRIC_SHAPES[i]);
			break;
		}
		++i;
	}
	if (!shape_match) 
	{
		PrintError(NO_GEOMETRIC_SHAPE_FOUND_ERROR, string, line_number);
	}
	else
	{
		if (!ispunct(string[geometric_shape_length]))
		{
			PrintError(NO_GEOMETRIC_SHAPE_FOUND_ERROR, string, line_number);
		}
		else
			if (string[geometric_shape_length] != '(')
			{
					PrintError(LEFT_PARENTHESIS_ERROR, string, line_number);
			}	
		}
}
	
	

struct Point
{
	double x;
	double y;
};


struct GeometricShapes
{
	struct Cirle
	{
		const struct Point center;
		const double radius;
	};

};


int main(int argc, char *argv[])
{
	FILE *file;
	file = fopen("geometry.txt", "r");
	if (file == NULL)
		PrintError(READ_FILE_ERROR, "", 0);																													
	else 
	{
		ssize_t str_len;
		char *string = NULL;																																																																																																																																															
		size_t len;
		int line_number = 0;
		int geometric_shapes_arr_size = sizeof(GEOMETRIC_SHAPES)/sizeof(GEOMETRIC_SHAPES[0]);
		while ((str_len = getline(&string, &len, file))!= EOF) 
        {
			if (string[str_len-1] == '\n')
				string = DeleteNewline(string, str_len);
			--str_len;
			++line_number;
			CatchError(string, geometric_shapes_arr_size, str_len, line_number);
        }	


	fclose(file);
	}
	return 0;
}
