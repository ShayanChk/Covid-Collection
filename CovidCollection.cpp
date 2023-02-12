//Name: Shayan Chabook
//student ID: 159844208
//email:schabook@myseneca.ca
//7/17/2022

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include "CovidCollection.h"

using namespace std;

namespace sdds {

    CovidCollection::CovidCollection(string filename)
    {
        fstream theFile(filename);
        if (!theFile.is_open())
        {
            throw runtime_error("Unable to open file " + filename);
        }

        while (theFile) 
        {

            string m_line, city, country, numOfCases, year, numOfDeaths, variant;
            Covid newCovid;

            getline(theFile, m_line, '\n');

            country = m_line.substr(0, 25);
            trim(country, m_line, 25);

            city = m_line.substr(0, 25);
            trim(city, m_line, 25);

            variant = m_line.substr(0, 25);
            trim(variant, m_line, 25);

            year = m_line.substr(0, 5);
            trim(year, m_line, 5);

            numOfCases = m_line.substr(0, 5);
            trim(numOfCases, m_line, 5);

            numOfDeaths = m_line.substr(0, 5);
            trim(numOfDeaths);

            newCovid.country = country;

            newCovid.city = city;

            newCovid.variant = variant;

            stringstream s1(numOfCases);
            s1 >> newCovid.numOfCases;

            stringstream s2(year);
            s2 >> newCovid.year;

            stringstream s3(numOfDeaths);
            s3 >> newCovid.m_deaths;

            covid.push_back(newCovid);
        }
        covid.pop_back();
    }

    void CovidCollection::display(ostream& out) const 
    {
        for_each(covid.begin(), covid.end(), [&out](const Covid& covid) {out << covid << endl; });

        auto totalCases = accumulate(covid.begin(), covid.end(), 0, [](int sum, const Covid& c) {return sum + c.numOfCases; });
        auto totalDeaths = accumulate(covid.begin(), covid.end(), 0, [](int sum, const Covid& c) {return sum + c.m_deaths; });
        
        out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');

        out << "|" << right << setw(80) << "Total Cases Around the World:  " << totalCases << " |" << endl;
        out << "|" << right << setw(80) << "Total Deaths Around the World:  " << totalDeaths << " |" << endl;
    }

    void CovidCollection::sort(string criteria) 
    {
        if (criteria == "country")
        {
            std::sort(covid.begin(), covid.end(), [](Covid c1, Covid c2) {return c1.country < c2.country; });
        }
        else if (criteria == "variant")
        {
            std::sort(covid.begin(), covid.end(), [](Covid c1, Covid c2) {return c1.variant < c2.variant; });
        }
        else if (criteria == "cases")
        {
            std::sort(covid.begin(), covid.end(), [](Covid c1, Covid c2) {return c1.numOfCases < c2.numOfCases; });
        }
        else if (criteria == "deaths")
        {
            std::sort(covid.begin(), covid.end(), [](Covid c1, Covid c2) {return c1.m_deaths < c2.m_deaths; });
        }
    }

    void CovidCollection::cleanList() 
    {
        for_each(covid.begin(), covid.end(), [](Covid& theCovid) {theCovid.variant = theCovid.variant == "[None]" ? "" : theCovid.variant; });
    }

    bool CovidCollection::inCollection(string variant) const 
    {
        auto var = std::find_if(covid.begin(), covid.end(), [variant](const Covid& theCovid) {return theCovid.variant == variant; });
        return var != covid.end();
    }

    list<Covid> CovidCollection::getListForCountry(std::string country) const
    {
        auto cnt = count_if(covid.begin(), covid.end(),[country](const Covid& theCovid) {return theCovid.country == country; });

        list<Covid> matches(cnt);

        copy_if(covid.begin(), covid.end(), matches.begin(), [country](const Covid& theCovid) {return theCovid.country == country; });

        return matches;
    }

    list<Covid> CovidCollection::getListForVariant(std::string variant) const
    {
        auto quantity = count_if(covid.begin(), covid.end(),[variant](const Covid& c) {return c.variant == variant; });

        list<Covid> matches(quantity);
        copy_if(covid.begin(), covid.end(), matches.begin(),
            [variant](const Covid& c) {return c.variant == variant; });

        return matches;
    }

    ostream& operator<<(ostream& out, const Covid& theCovid)
    {
        out << "| " << left << setw(20) << theCovid.country << "  | ";
        out << left << setw(15) << theCovid.city << " | ";
        out << left << setw(20) << theCovid.variant << " | ";
        out << right << setw(6) << (theCovid.year > 0 ? to_string(theCovid.year) : "") << " | ";
        out << right << setw(4) << (theCovid.numOfCases > 0 ? to_string(theCovid.numOfCases) : "") << " | ";
        out << right << setw(3) << (theCovid.m_deaths > 0 ? to_string(theCovid.m_deaths) : "") << " |";
        return out;
    }

    void CovidCollection::trim(string& str)
    {
        str.erase(str.find_last_not_of(' ') + 1);
        str.erase(0, str.find_first_not_of(' '));
    }

    void CovidCollection::trim(string& str, string& line, int n)
    {
        trim(str);
        line.erase(0, n);
    }

} 