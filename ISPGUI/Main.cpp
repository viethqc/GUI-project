#include "resources.cpp" // packed /res/ folder
#include "Frame.h"
#include "WriteLog.h"
#include "Extractor.h"

int uimain(std::function<int()> run ) 
{
	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

	CFrame *pwin = new CFrame();
	// note: this:://app URL schema is dedicated to the sciter::archive content associated with the application
	
	pwin->expand();
	  
	return run(); 
}