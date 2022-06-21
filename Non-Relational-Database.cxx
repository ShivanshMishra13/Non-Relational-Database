#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <map>
#include <algorithm>

class Result
{
  public:
    bool Success = true;
    bool Faliure = false;
};
class Settings
{
  public:
    std::string path;
    bool isPath;
};
class Sanitizer
{
  public:
    std::string SafeCon = "";

    std::string sanitize(std::string text)
    {
        for (char i : text)
        {
            if (i == ':')
            {
            }
            else if (i == ';')
            {
            }
            else
            {
                SafeCon = SafeCon + i;
            }
        }
        // std::cout << SafeCon << std::endl;
        return SafeCon;
    }
};
class Helpers
{
  public:
    void PrintMap(std::map<std::string, std::string> kv)
    {
        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            std::cout << it->first + "-" + it->second << std::endl;
        }
    }
    bool IsPathExist(const std::string &s)
    {
        struct stat buffer;
        return (stat(s.c_str(), &buffer) == 0);
    }
};

class Lexer
{
  private:
    ;
    int curr_l = 0;

  public:
    Lexer()
    {
    }
    void advance()
    {
        this->curr_l++;
        //return this->curr_l;
    }
    void setZero()
    {
        this->curr_l = 0;
    }

    std::map<std::string, std::string> Update(std::string kxy, std::string xvalue, std::string path)
    {
        Sanitizer sz = Sanitizer();

        std::string key = sz.sanitize(kxy);
        std::ifstream File(path);

        std::string content;
        std::string text;

        // File >> content;
        while (!File.eof())
        { // keep reading until end-of-file
            text += content;
            File >> content; // sets EOF flag if no value found
        }
        Helpers h = Helpers();

        char s = ';';
        char c = ':';
        std::map<std::string, std::string> kv;
        std::string result;

        while (text.length() > this->curr_l)
        {
            if (text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                while (text[this->curr_l] != s)
                {
                    temp = temp + text[this->curr_l];
                    this->advance();
                }
                if (result == key)
                {
                    kv[result] = xvalue;
                }
                else
                {
                    kv[result] = temp;
                }
                result = "";
                temp = "";
            }
            if (text[this->curr_l] == s)
            {
                this->advance();
            }
            result = result + text[this->curr_l];
            this->advance();
        }

        // kv["ret-val"] = "faliure";
        std::ofstream Sile(path, std::ios::trunc);

        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            // char input[]=it->first + ":" + it->second + ";" + "\n";

            Sile << it->first + ":" + it->second + ";" + "\n";
        }
        std::string gs;
        File >> gs;
        std::cout << gs << std::endl;
        File.close();
        kv["ret-val"] = "success";
        //      h.PrintMap(kv);

        return kv;
    }

    std::map<std::string, std::string> Delete(std::string kxy, std::string path)
    {
        Sanitizer sz = Sanitizer();

        std::string key = sz.sanitize(kxy);
        std::ifstream File(path);

        std::string content;
        std::string text;

        // File >> content;
        while (!File.eof())
        { // keep reading until end-of-file
            text += content;
            File >> content; // sets EOF flag if no value found
        }
        Helpers h = Helpers();

        char s = ';';
        char c = ':';
        std::map<std::string, std::string> kv;
        std::string result;

        while (text.length() > this->curr_l)
        {
            if (text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                while (text[this->curr_l] != s)
                {
                    temp = temp + text[this->curr_l];
                    this->advance();
                }
                if (result == key)
                {
                    //std::cout<<"match"<<std::endl;//INTENTIONALLY
                }
                else
                {
                    kv[result] = temp;
                }
                result = "";
                temp = "";
            }
            if (text[this->curr_l] == s)
            {
                this->advance();
            }
            result = result + text[this->curr_l];
            this->advance();
        }

        // kv["ret-val"] = "faliure";
        std::ofstream Sile(path, std::ios::trunc);

        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            // char input[]=it->first + ":" + it->second + ";" + "\n";

            Sile << it->first + ":" + it->second + ";" + "\n";
        }
        std::string gs;
        File >> gs;
        std::cout << gs << std::endl;
        File.close();
        kv["ret-val"] = "success";
        //    h.PrintMap(kv);

        return kv;
    }

    std::map<std::string, std::string> search(std::string path, std::string kxy)
    {
        Sanitizer sz = Sanitizer();

        std::string key = sz.sanitize(kxy);
        std::ifstream File(path);

        std::string content;
        std::string text;

        // File >> content;
        while (!File.eof())
        { // keep reading until end-of-file
            text += content;
            File >> content; // sets EOF flag if no value found
        }
        //  std::cout << text << std::endl;
        char s = ';';
        char c = ':';
        std::map<std::string, std::string> kv;
        std::string result;

        while (text.length() > this->curr_l)
        {
            if (text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                while (text[this->curr_l] != s)
                {
                    temp = temp + text[this->curr_l];
                    this->advance();
                }
                if (result == key)
                {
                    kv["ret-val"] = "success";
                    kv[result] = temp;
                    return kv;
                }
                result = "";
                temp = "";
            }
            if (text[this->curr_l] == s)
            {
                this->advance();
            }
            result = result + text[this->curr_l];
            this->advance();
        }
        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            std::cout << it->first + "-" + it->second << std::endl;
        }
        kv["ret-val"] = "faliure";
        return kv;
    }

    std::map<std::string, std::string> gen_tok(std::string path)
    {
        std::ifstream File(path);

        std::string content;
        std::string text;

        // File >> content;
        while (!File.eof())
        { // keep reading until end-of-file
            text += content;
            File >> content; // sets EOF flag if no value found
        }
        char s = ';';
        char c = ':';
        std::map<std::string, std::string> kv;
        std::string result;

        while (text.length() > this->curr_l)
        {
            if (text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                while (text[this->curr_l] != s)
                {
                    temp = temp + text[this->curr_l];
                    this->advance();
                }
                kv[result] = temp;
                result = "";
                temp = "";
            }
            if (text[this->curr_l] == s)
            {
                this->advance();
            }
            result = result + text[this->curr_l];
            this->advance();
        }
        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            std::cout << it->first + "-" + it->second << std::endl;
        }

        return kv;
    }
};

class Database
{
  public:
    Settings set;
    std::string path;
    static int counter;

    Database(Settings &s)
    {
        this->set = s;
        this->path = this->set.path;
    }

    bool MKDB()
    {
        Helpers hp = Helpers();
        Result res = Result();
        if (hp.IsPathExist("./Database"))
        {
            return res.Faliure;
        }
        system("mkdir Database");
        return res.Success;
    }

    bool CreateSet(std::string Set_name, std::map<std::string, std::string> kv)
    {
        // NEED CONTENT SANITAIZATION
        std::ofstream File("./Database/" + Set_name, std::ofstream::out | std::ofstream::trunc);
        Sanitizer sz = Sanitizer();

      

        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            
            // char input[]=it->first + ":" + it->second + ";" + "\n";

            File <<it->first+ ":" +it->second + ";" + "\n";
        }
        File.close();
    }

    std::map<std::string, std::string> getMap(std::string filepath)
    {
        //        std::ifstream File(filepath + ".sm");

        //        std::string content;
        //        std::string temp;

        //        // File >> content;
        //        while (!File.eof())
        //        { // keep reading until end-of-file
        //            temp += content;
        //            File >> content; // sets EOF flag if no value found
        //        }

        Lexer lx = Lexer();
        std::map<std::string, std::string> output = lx.gen_tok(filepath);
        return output;

        // std::cout<<content<<std::endl;
    }
    std::map<std::string, std::string> search(std::string key, std::string filepath)
    {
        Lexer lx = Lexer();
        std::map<std::string, std::string> output = lx.search(filepath, key);

        return output;
    }
};

int main()
{
    Settings s = Settings();
    std::string name = "Users";
    Database db = Database(s);

    std::map<std::string, std::string> KV;
    KV["RollNo"] = "34";
    KV["houseno"] = "374";
    KV["game"] = "bgmi";
    KV["friend"] = "none";
    KV["name"] = "shivansh";
     db.CreateSet("Users", KV);

    //"    std::string s="hdusjsksiznzbdhsjdh";
    Lexer lx = Lexer();

    std::map<std::string, std::string> ot = db.search("friend", "./Database/Users");

    //    std::cout<<txt<<std::endl;
 //   lx.Update("friend;:", "Brij", "./Database/Users");

    std::cout << ot["friend"];
}