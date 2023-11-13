#ifndef SDDS_PACK_H_
#define SDDS_PACK_H_

#include "Container.h"

namespace sdds {


	// =-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	// 
	//	 TODO:
	//		"Container" class ambuigious in main.cpp (May be because of include in Pack.h and in main.cpp)
	// 
	// =-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


	class Pack : public Container {

	private:
		int UnitSize; // 330 CC for a can of coke, or 250 CC for a bottle of water
		int Size;
		int NumOfUnits;

	public:
		Pack(const char* nContent, int nSize, int nUnitSize = 330, int nNumOfUnits = 0);
		int operator+=(int units);
		int operator-=(int units);
		int unit();
		int noOfUnits();
		int size();

		void clear(int nPackSize, int nUnitSize, const char* nContent);
		std::ostream& print(std::ostream& ostr);
		std::istream& read(std::istream& istr);

		friend std::ostream& operator<<(std::ostream& ostr, Pack& p);
		friend std::istream& operator>>(std::istream& istr, Pack& p);
	};
}

#endif