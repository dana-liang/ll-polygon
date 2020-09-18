/* CS211 Summer 2020 Project 3
 *
 * dliang26-proj3.c
 * By Dana Liang, 5/25/2020
 * 
 * This program maintains a linked list of integers, representing a set of vertices that makes up a polygon
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

int debugMode = FALSE; // Global variable debugMode: print debugging information if set to true

/* PointNode data type */
typedef struct pointNode
{
    int ID;			// vertex number
    struct pointNode* next;	// pointer to the next PointNode in the list
} PointNode;

/* Polygon data type */
typedef struct
{
    PointNode* points;	// head of the linked list
    int nPoints;	// number of points in the Polygon currently
    int min, max;	// maximum and minimum vertex indices in the Polygon
} Polygon;

/************************* 
 * FUNCTION DECLARATIONS *
 *************************/

int addVertexToPolygon( Polygon* polygon, int vertexID );

PointNode* findVertexInPolygon( Polygon polygon, int vertexID );

int size( Polygon polygon );

int isEmpty( Polygon polygon );

int removeVertexFromPolygon( Polygon *polygon );

/****************** 
 *      MAIN      *
 ******************/

int main ( int argc, char const *argv[] )
{
    /*print information for debugging if "-d" is given as a command line argument */
    for ( int i = 0; i < argc; i++ )
    {
        if ( strcmp ("-d", argv[i]) == 0 )
		debugMode = TRUE;
	else
		debugMode = FALSE;
    }

    /* declare a Polygon and initialize the pointer and nPoints inside it */
    Polygon polygon;
    polygon.points = NULL;
    polygon.nPoints = 0;
    
    /* Read data for the vertices comprising a Polygon (build a polygon) from standard input */
    /* Read data until a negative integer is read */
    
    printf("Enter a list of integers to add as vertices to a polygon. Terminate your list with a negative integer.\n");

    int val;
    scanf( "%d", &val );

    while ( val >= 0 )
    {
        addVertexToPolygon ( &polygon, val );
        polygon.nPoints++;
	scanf( "%d", &val );
    }

    PointNode* current = polygon.points;

    if ( debugMode == TRUE ) 
    {

	if ( isEmpty ( polygon ) )
		printf("The list is empty.\n");

	printf("# of Points: %d\nList: ", size( polygon ) );

	for ( current = polygon.points; current != NULL; current = current->next )
		printf( "%d ", current->ID );
	printf("\n");
    } 


    /* Report the Polygon's number of vertices, the specific list of vertex indecies, 
             and the minimum and maximum indices in the list.                           
    */
    
    if ( isEmpty ( polygon ) == 1 )
	    printf("The list is empty.\n");

    else
    {
        printf("# of vertices in the polygon: %d\nList: ", size ( polygon ) );
    

        /* Find maximum and minimum vertex indices, and print the list */
        polygon.min = polygon.points->ID;
        polygon.max = polygon.points->ID;
        for (current = polygon.points; current != NULL; current = current->next )
        {
            if ( current->ID > polygon.max )
		polygon.max = current->ID;

	    if ( current->ID < polygon.min )
		polygon.min = current->ID;

	    printf("%d ", current->ID);
        }
  
        printf("\nMinimum: %d	Maximum: %d\n", polygon.min, polygon.max);
    

    /* Read data for a second set of vertices, and for each vertex ID search the Polygon's list of vertices, 
             if a matching vertex ID is found, report the address of the PointNode where the ID was found. 
    */
    /* Read data until a negative integer is read */
    
        printf("Enter another list of integer vertices and terminate with a negative integer" 
		    " to check if they are in the polygon:\n");
        scanf("%d", &val);

        while ( val >= 0 )
        {
            if ( findVertexInPolygon( polygon, val ) != NULL )
		printf("\nVertex %d found at %p.\n", val, findVertexInPolygon( polygon, val ) );
	    else
		printf("\nVertex %d not found.\n", val);

	    scanf("%d", &val);
        }
    }

    /* Free all dynamically allocated memory before the program ends.*/

    while ( removeVertexFromPolygon( &polygon ) != -1 )  
	    removeVertexFromPolygon( &polygon );


    return 0;
}

/************************ 
 * FUNCTION DEFINITIONS *
 ************************/

/* Return 0 if vertexID is successfully added to the polygon, -1 otherwise */
int addVertexToPolygon( Polygon* polygon, int vertexID )
{    
    if ( polygon == NULL )
	    return -1;
    
    PointNode* temp = (PointNode*) malloc ( sizeof(PointNode) );
    temp->ID = vertexID;
    temp->next = polygon->points;
    polygon->points = temp;

    return 0;
}

/* Return the address of the PointNode where the vertexID was found, NULL if not found */
PointNode* findVertexInPolygon( Polygon polygon, int vertexID )
{
    PointNode* current = polygon.points;
    for ( current = polygon.points; current != NULL; current = current->next )
	    if ( current->ID == vertexID ) 
		    return current;

    return NULL;
}

/* Return number of vertices in the polygon */
int size( Polygon polygon )
{
    return polygon.nPoints;
}

/* Return 1 if there are no vertices in the polygon, 0 otherwise */
int isEmpty( Polygon polygon )
{
    if ( polygon.nPoints == 0 )
	    return 1;
    else
	    return 0;
}

/* Remove 1 vertex from the polygon (from the head of the linked list) and free the memory associated with that PointNode.
 * Return the ID of the removed vertex if successfully removed, -1 otherwise */
int removeVertexFromPolygon( Polygon *polygon )
{
    PointNode* temp = NULL;
    int ID;

    if ( polygon->points == NULL )
	    return -1;

    temp = polygon->points;
    ID = temp->ID;
    polygon->points = polygon->points->next;
    temp->next = NULL;
    free(temp);
    
    return ID;
}
