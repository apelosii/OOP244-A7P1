#ifndef SDDS_CONTAINER_H_
#define SDDS_CONTAINER_H_

#include <cstring>
#include <istream>
#include <ostream>
#include <iostream>

namespace sdds {

	class Container {

	private:
		char* Content;
		int Capacity;
		int ContentVolume;

	protected:
		void setEmpty();
		int capacity();
		int volume();

	public:

		Container(const char* newContent, int newCapacity, int newContentVolume = 0);
		~Container();
		int operator+=(int volume);
		int operator-=(int volume);
		operator bool() const;
		void clear(int nCapacity, const char* nContent);
		std::ostream& print(std::ostream& ostr);
		std::istream& read(std::istream& istr);

		friend std::ostream& operator<<(std::ostream& ostr, Container& c);
		friend std::istream& operator>>(std::istream& istr, Container& c);

	};

}

#endif