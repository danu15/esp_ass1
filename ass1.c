//-----------------------------------------------------------------------------
// ass1.c
//
// <Explanation of the program ...>
// <... May have multiple lines.>
//
// Group: Group 17553, study assistant Florian Hager
//
// Authors: Weibold Johannes 01616134
// Unger Daniel 0
//-----------------------------------------------------------------------------
//

#define MAX_USER_INPUT 256

#define TRIPLET_MAX 3

#define USER_INPUT_ERROR_CODE -1


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

//-----------------------------------------------------------------------------
///
/// This is an example header comment. Copypaste and adapt it!
///
/// @param human The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return int age of spouse
//
int validateTriangleNumberInput()
{
	char line[MAX_USER_INPUT];
	char invalid_character;
	int number_triangles = 0;
	
	for(;;)
	{
		printf("Please enter the number of triangles to check: ");
		if( fgets(line, sizeof(line), stdin) == NULL)
		{
			// EOF reached.
			return EOF;
		}
		
    if (sscanf(line, "%d %c", &number_triangles, &invalid_character ) == 1)
		{
			if( number_triangles >= 1 && number_triangles <= UCHAR_MAX )
			{
				return number_triangles;
			}
		}
		printf("[ERR] Invalid number of triangles.\n");
	}
}

//-----------------------------------------------------------------------------
///
/// This is an example header comment. Copypaste and adapt it!
///
/// @param human The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return int age of spouse
//
void tripletInputMessages( int triplet_index )
{
	switch( ++triplet_index )
	{
		case 1:
			printf("Please enter the first number of the triplet: ");
			break;
		case 2:
			printf("Please enter the second number of the triplet: ");
			break;
		case 3:
			printf("Please enter the third number of the triplet: ");
			break;
		default:
			// no message
			break;
	}
}

//-----------------------------------------------------------------------------
///
/// This is an example header comment. Copypaste and adapt it!
///
/// @param human The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return int age of spouse
//
float tripletValueInput(int triplet_index)
{
	char line[MAX_USER_INPUT];
	char invalid_character;
	float triplet_value = 0.0;
	
	for(;;)
	{
		tripletInputMessages( triplet_index );
		if( fgets(line, sizeof(line), stdin) == NULL)
		{
			// EOF reached.
			return EOF;
		}
		
    if (sscanf(line, "%f %c", &triplet_value, &invalid_character ) == 1)
		{
			if( triplet_value > 0.0 && triplet_value < FLT_MAX )
			{
				return triplet_value;
			}
		}
		printf("[ERR] Invalid number for the triplet.\n");
	}
}

//-----------------------------------------------------------------------------
///
/// This is an example header comment. Copypaste and adapt it!
///
/// @param human The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return int age of spouse
//
int readTriplets(float triangles[][TRIPLET_MAX], int triangle_count)
{
	int triangle_counter;
	int triplet_counter;
	
	float triplet_value = 0;
	
	for( triangle_counter = 0; triangle_counter < triangle_count; triangle_counter++ )
	{
		for( triplet_counter = 0; triplet_counter < TRIPLET_MAX; triplet_counter++ )
		{
			triplet_value = tripletValueInput( triplet_counter );
			if( triplet_value == EOF )
			{
				// EOF reached.
				return 0;
			}
			
			triangles[ triangle_counter ][ triplet_counter ] = triplet_value;
		}
	}
	
	return 1;
}


//-----------------------------------------------------------------------------
///
/// This is an example header comment. Copypaste and adapt it!
///
/// @param human The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return void
//
void insertionSort(float sort[], int length)
{
   int i,j;
	 float value;
	 
   for (i = 1; i < length; i++)
   {
       value = sort[i];
       j = i - 1;
 
       while (j >= 0 && sort[j] > value)
       {
           sort[j+1] = sort[j];
           j = j-1;
       }
       sort[j+1] = value;
   }
}

//-----------------------------------------------------------------------------
///
/// This is an example header comment. Copypaste and adapt it!
///
/// @param human The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return int age of spouse
//
void sortTriplets(float triangles[][TRIPLET_MAX], int triangle_count)
{
	int triangle_counter;
	
	for( triangle_counter = 0; triangle_counter < triangle_count; triangle_counter++ )
	{
			insertionSort( triangles[triangle_counter], TRIPLET_MAX );
	}
}


int isTriangle( int number, float a, float b, float c )
{
		if( ( a + b ) > c )
		{
			printf("Triplet %d (a=%f, b=%f, c=%f) is a triangle.\n", number, a, b, c);
			return 1;
		}
		printf("Triplet %d (a=%f, b=%f, c=%f) is NO triangle.\n", number, a, b, c);
		return 0;
}

void verifyTriangleTypes( float a, float b, float c )
{
		if( ( a == b ) || ( a == c ) || ( b == c ) )
		{
			if( (a == b ) && ( b == c ) )
			{
				printf("  It is an equilateral triangle.\n");
			}
			printf("  It is an isosceles triangle.\n");
		}
		
		if( ( c * c ) == ( ( a * a ) + ( b * b ) ) )
		{
			printf("  It is a right triangle.\n");
		}
}



void evaluateTriangleTypes(float triangles[][TRIPLET_MAX], int triangle_count)
{
	float a;
	float b;
	float c;
	
	int triangle_counter;
	int triangle_number;
	
	for( triangle_counter = 0; triangle_counter < triangle_count; triangle_counter++ )
	{
		// store triplet values for evaluation
		a = triangles[triangle_counter][0];
		b = triangles[triangle_counter][1];
		c = triangles[triangle_counter][2];
		
		triangle_number = triangle_counter + 1;
		
		// triangle inequality
		if( isTriangle( triangle_number, a, b, c) )
		{
			// triangle types
			verifyTriangleTypes( a, b, c);
		}
	}
}

//------------------------------------------------------------------------------
///
/// The main program.
/// triangle calculation tool.
/// Reads a given number of triangle triplets from the users input.
/// Sort the triplets ascending and outputs triangle type.
///
/// @param argc not used
/// @param argv not used
///
/// @return always zero
//
int main( int argc, const char* argv[] )
{
	int triangle_count = 0;

	// validate userinput for triangle numbers.
	triangle_count = validateTriangleNumberInput();
	if( triangle_count > 0 )
	{	
		float triangles[triangle_count][TRIPLET_MAX];
		
			// read and validate triplets from userinput.
		if( readTriplets( triangles, triangle_count) > 0 )
		{
			// sort triplets ascending
			sortTriplets( triangles, triangle_count );
			
			// evaluate triangle types
			evaluateTriangleTypes( triangles, triangle_count );
		}
	}
	
	return 0;
}
