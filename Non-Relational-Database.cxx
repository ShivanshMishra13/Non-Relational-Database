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

class Helpers
{
  public:
    bool IsPathExist(const std::string &s)
    {
        struct stat buffer;
        return (stat(s.c_str(), &buffer) == 0);
    }
};


class Lexer
{
  private:;
    int curr_l = 0;

  public:
    std::string text;
    Lexer(std::string &content)
    {
        this->text = content;
    }
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
    std::map<std::string, std::string> search(std::string key)
    {
        char s = ';';
        char c = ':';
        std::map<std::string, std::string> kv;
        std::string result;

        while (this->text.length() > this->curr_l)
        {
            if (this->text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                while (this->text[this->curr_l] != s)
                {
                    temp = temp + this->text[this->curr_l];
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
            if (this->text[this->curr_l] == s)
            {
                this->advance();
            }
            result = result + this->text[this->curr_l];
            this->advance();
        }
        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            std::cout << it->first + "-" + it->second << std::endl;
        }
        kv["ret-val"] = "faliure";
        return kv;
    }

    std::map<std::string, std::string> gen_tok()
    {
        char s = ';';
        char c = ':';
        std::map<std::string, std::string> kv;
        std::string result;

        while (this->text.length() > this->curr_l)
        {
            if (this->text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                while (this->text[this->curr_l] != s)
                {
                    temp = temp + this->text[this->curr_l];
                    this->advance();
                }
                kv[result] = temp;
                result = "";
                temp = "";
            }
            if (this->text[this->curr_l] == s)
            {
                this->advance();
            }
            result = result + this->text[this->curr_l];
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
        std::ofstream File("./Database/" + Set_name + ".sm");

        for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            // char input[]=it->first + ":" + it->second + ";" + "\n";

            File << it->first + ":" + it->second + ";" + "\n";
        }
        File.close();
    }
    
    std::map<std::string, std::string> getMap(std::string filepath)
    {
        std::ifstream File(filepath + ".sm");

        std::string content;
        std::string temp;

        // File >> content;
        while (!File.eof())
        { // keep reading until end-of-file
            temp += content;
            File >> content; // sets EOF flag if no value found
        }

        Lexer lx = Lexer(temp);
        std::map<std::string, std::string> output = lx.gen_tok();
        return output;

        // std::cout<<content<<std::endl;
    }
    std::map<std::string, std::string> search(std::string key, std::string filepath)
    {
        std::ifstream File(filepath + ".sm");

        std::string content;
        std::string temp;

        while (!File.eof())
        {
            temp += content;
            File >> content;
        }
        Lexer lx = Lexer(temp);
        std::map<std::string, std::string> output = lx.search(key);

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
   // Lexer lx = Lexer();

    std::map<std::string, std::string> ot = db.search("game", "./Database/Users");

    //    std::cout<<txt<<std::endl;

    std::cout << ot["ret-val"];
}