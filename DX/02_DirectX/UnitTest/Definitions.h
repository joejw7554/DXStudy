#pragma once

#define Delete(x)\
{\
	if ((x) != nullptr)\
	{\
		delete (x);\
		(x) = nullptr;\
	}\
}


#define Release(x)\
{\
	if ((x) != nullptr)\
	{\
		(x)->Release();\
		(x) = nullptr;\
	}\
}

#define Check(x) {assert ((x)>=0);}