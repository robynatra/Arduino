#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <cctype>
using   namespace   std; 

typedef vector<string> StringArray_t;
typedef pair<string,string> StringPair_t;

class StringUtil
{
public:

    static void Split(string& s, string& delim, StringArray_t& ret)
    {
        size_t last = 0;
        size_t index=s.find_first_of(delim,last);
        while (index != string::npos)
        {
            ret.push_back(s.substr(last,index-last));
            last=index+delim.length();
            index=s.find_first_of(delim,last);
        }
        if (last < s.length())
        {
            ret.push_back(s.substr(last));
        }
    } 
    
    static void Split(string& s, char delim, StringArray_t& ret)
    {
        size_t last = 0;
        size_t index=s.find_first_of(delim,last);
        while (index != string::npos)
        {
            ret.push_back(s.substr(last,index-last));
            last=index+1;
            index=s.find_first_of(delim,last);
        }
        if (last < s.length())
        {
            ret.push_back(s.substr(last));
        }
    } 

    static void Split(string& s, char delim, StringPair_t& ret)
    {
        size_t last = 0;
        size_t index=s.find_first_of(delim,last);
        if(index != string::npos)
        {
            ret.first = s.substr(last,index-last);
            last=index+1;
            ret.second = s.substr(last);
        }
    } 

    static string& LTrim(string &ss)
    {
#if 0    
        int   (*pf)(int)=isspace;
        string::iterator   p=find_if(ss.begin(),ss.end(),not1(ptr_fun(pf)));
        ss.erase(ss.begin(),p);
        return   ss;
#endif

        const char drop = ' ';
        // trim left
        return ss.erase(0,ss.find_first_not_of(drop));     

    }

    static string& RTrim(string &ss)
    {
#if 0
        int   (*pf)(int)=isspace;
        string::reverse_iterator   p=find_if(ss.rbegin(),ss.rend(),not1(ptr_fun(pf)));
        ss.erase(p.base(),ss.end());
        return   ss;
#endif
        const char drop = ' ';
        // trim right
        return ss.erase(ss.find_last_not_of(drop)+1);        
 
    }

    static string& Trim(string &ss)
    {
        LTrim(RTrim(ss));
        return ss;
    }
    
};


#endif 


