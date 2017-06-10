#define SAFE_DELETE(x)      {if ((x) != NULL) {delete x; x = NULL;}} 
#define SAFE_DELETE_ARRAY(x)      {if ((x) != NULL) {delete [] x; x = NULL;}} 