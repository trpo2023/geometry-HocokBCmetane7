#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define READ_FILE_ERROR -1 
#define NO_GEOMETRIC_SHAPE_FOUND_ERROR -2
#define LEFT_PARENTHESIS_ERROR -3
#define RIGHT_PARENTHESIS_ERROR -4
#define UNEXPECTED_TOKEN_ERROR -5
#define NO_TYPE_CAST_ERROR -6        


char *(GEOMETRIC_SHAPES[]) = {"circle", "triangle", "polygon"};


void CatchError(char*, const int, const int, const int);
void PrintError(const int, const char*, const int);
int FindShape(const char*, const char*, const int, const int);
char* DeleteNewline(const char *string, const int str_len);
bool ReadArguments(char* string);
char* FormatArgumentString(char*, int, char*, char*);
int CountSymbol(char* begin, char* end, char symbol);




bool ReadArguments(char* string)
{
	bool valid_argument = true;
	char* begin;
	char* end;
	char* string_copy;
	int str_len = strlen(string);
	int unnecessary_spaces = 0;
	int arguments_amount;

	if (isspace(string[str_len-1]))
	{
		++unnecessary_spaces;
	}

	if (isspace(string[0]))
	{
		++string;
		//++unnecessary_spaces;
		--str_len;
	}
	begin = end = string;
	
	double arr[CountSymbol(string, string+str_len, ' ')-unnecessary_spaces+1];

	int i = 0;
	while (*end != '\0')
	{
		while(!isspace(*end))
		{
			if (*end =='.' && *(end+1) == '.' || (isalpha(*end) || (ispunct(*end) && *end != '.')) && *end != '\0')
				return 0;
			if (*end == '\0')
				break;
			++end;
		}
		string_copy = malloc(end-begin);
		for(int i = 0; begin+i != end; ++i)
		{
			string_copy[i] = *(begin+i);
		}
	
		if ((!atof(string_copy)))
		{
			valid_argument = false;
			break;
		}
		arr[i] = atof(string_copy);
		++i;
		free(string_copy);
		++end;
		begin = end;
	}
	return valid_argument;
}


int CountSymbol(char* begin, char* end, char symbol)
{
	int i = 0;
	int count = 0;
	while (begin+i != end)
	{
		if (*(begin+i) == symbol)
			++count;
		++i;
	}
	return count;
}


int CountDoubleSpace(char* begin, char* end)
{
	int i = 0;
	int double_space_count = 0;
	while (begin+i != end)
	{
		if ((*(begin+i) == ' ') && (*(begin+i+1) == ' '))
			++double_space_count;
		++i;
	}
	return double_space_count;
}


char* FormatArgumentString(char* string, int str_len, char* begin, char* end)
{
	str_len = end-begin;			//with '\0'
	char* string_copy = malloc(str_len);
	int i = 0, j = 0;
	int comma_count = CountSymbol(begin, end, ',');
	int double_space_count = CountDoubleSpace(begin, end);
	
	
	++begin;

	while (*(begin+i) != *end)
	{
		string_copy[i] = *(begin+i);		// take arguments without '()'
		++i;
	}
	string_copy[i] = '\0';
	i = 0;
	
	
	str_len -= comma_count;					// with '\0'
	char* string_copy2 = malloc(str_len);
	while (string_copy[i] != '\0')
	{
		if (string_copy[i] != ',')
		{
			string_copy2[j] = string_copy[i];
			++j;
		}
		++i;
	}
	string_copy2[j] = '\0';
	i = 0, j = 0;
	
	str_len -= double_space_count;
	free(string_copy);
	string_copy = malloc(str_len);
	while (string_copy2[i] != '\0')
	{
		if (string_copy2[i] != ' ' || string_copy2[i+1] != ' ')
		{
			string_copy[j] = string_copy2[i];
			++j;
		}
		++i;
	}
	string_copy[j] = '\0';
	return string_copy;
}


char* ToLower(const char * const string, const int str_len)
{
	int i = 0;
	char* const string_copy = malloc(str_len+1);
	while (string[i] != '\0')
	{
		string_copy[i] = tolower(string[i]);
		++i;
	}
	string_copy[str_len] = '\0';
	return string_copy;
}


char* DeleteNewline(const char *string, const int str_len)
{
	char * const string_copy = malloc(str_len);
	for (int i = 0; i < str_len-1; i++)
	{
		string_copy[i] = string[i];
	}
	string_copy[str_len-1] = '\0';
	return string_copy;
}


int FindShape(const char * string, const char *geometric_shape, const int str_len, const int geometric_shape_length)
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
		printf("%s %d: %s\n\n%s\n\n\n", "Error in line",	line_number, string, "Expected ')'");
		break;
	case UNEXPECTED_TOKEN_ERROR:
		printf("%s %d: %s\n\n%s\n\n\n", "Error in line",	line_number, string, "Unexpected token");
		break;
	case NO_TYPE_CAST_ERROR:
		printf("%s %d: %s\n\n%s\n\n\n", "Error in line",	line_number, string, "Expected '<double>'");
		break;
	default:
	printf("%s", "Unknown error.");
		break;
	}
	
}


void CatchError(char* string, const int geometric_shapes_arr_size, const int str_len, const int line_number)
{
	int i = 0;
	bool shape_match = false;
	int geometric_shape_length = strlen(GEOMETRIC_SHAPES[i]);
	char *right_parenthesis = NULL, *argument = NULL;  // !!!rename
	char *left_parenthesis;

	while(i < geometric_shapes_arr_size)
	{
		shape_match = FindShape(string, GEOMETRIC_SHAPES[i], str_len, geometric_shape_length); 
		if (shape_match)
		{
			shape_match = true;
			geometric_shape_length = strlen(GEOMETRIC_SHAPES[i]);
			break;
		}
		++i;
	}
	left_parenthesis = &string[geometric_shape_length];
	if (!shape_match) 															//geometric shape wasn't found
		PrintError(NO_GEOMETRIC_SHAPE_FOUND_ERROR, string, line_number); 
	else
	{
		if (!ispunct(string[geometric_shape_length]))							//geometric shape was found, but there's an alpha
			PrintError(NO_GEOMETRIC_SHAPE_FOUND_ERROR, string, line_number);	// after it
		else
			
			if (string[geometric_shape_length] != '(')							//no '(' whatsoever
				{
					if (ispunct(string[geometric_shape_length]))				//if it's not alpha and not '(', but is punct)
						PrintError(NO_GEOMETRIC_SHAPE_FOUND_ERROR, string, line_number); //e.g '.'
					else
						PrintError(LEFT_PARENTHESIS_ERROR, string, line_number);
				}
			else
			{
				for (int i = geometric_shape_length; string[i] != ')' && string[i] != '\0'; i++)
				{
					if (string[i+1] == ')') 									//+1 in needed
					{
						right_parenthesis = &string[i+1];
						break;
					}
				}
				if (!right_parenthesis)
					PrintError(RIGHT_PARENTHESIS_ERROR, string, line_number);
				else
				{
					for (int i = 1; *(right_parenthesis+i) != '\0'; i++)
					{
						if (isalnum( *(right_parenthesis+i) ) || (ispunct(*(right_parenthesis+i)))) //anything after ')'
						{																			//but space
							PrintError(UNEXPECTED_TOKEN_ERROR, string, line_number);
							break;
						}
					}
					char* argument_string = FormatArgumentString(string, str_len, left_parenthesis, right_parenthesis);
					if (!ReadArguments(argument_string))
					{
						PrintError(NO_TYPE_CAST_ERROR, string, line_number);
					}
				}
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
			{
				string = DeleteNewline(string, str_len);
				--str_len;
			}
			string = ToLower(string, str_len); //can create new string to display the original string in console
			++line_number;
			CatchError(string, geometric_shapes_arr_size, str_len, line_number);
        }	


	fclose(file);
	}
	return 0;
}
