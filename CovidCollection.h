//Name: Shayan Chabook
//student ID: 159844208
//email:schabook@myseneca.ca
//7/17/2022

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace sdds {

    struct Covid {
        std::string country;
        std::string city;
        std::string variant;
        int numOfCases;
        int year;
        int m_deaths;
    };

    class CovidCollection {
    private:
        std::vector<Covid> covid;
        void trim(std::string& str);
        void trim(std::string& str, std::string& line, int n);

    public:

        CovidCollection(std::string filename);
        void display(std::ostream& out) const;
        void sort(std::string criteria);
        void cleanList();
        bool inCollection(std::string variant) const;
        std::list<Covid> getListForCountry(std::string country) const;
        std::list<Covid> getListForVariant(std::string variant) const;
       
    };

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

}

#endif //SDDS_COVIDCOLLECTION_H
