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
struct RES
{
    std::string arr[100];
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
    std::string delcomma(std::string text)
    {
        std::string t;

        for (char i : text)
        {
            if (i == ',')
            {
            }
            else
            {
                t = t + i;
            }
        }
        return t;
    }

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

    bool Update(std::string kxy, RES r, std::string path,std::string name)
    {
        std::map<std::string, RES> output;
        std::map<std::string, RES> gp = this->gen_tok(path);
        for (std::map<std::string, RES>::iterator it = gp.begin(); it != gp.end(); ++it)
        {
            if (it->first == kxy)
            {
                output[it->first] = r;
            }
            else
            {
                output[it->first] = it->second;
            }
        }
            
            try
            {
                this->CreateSetBackUse(name, output);
                return true;
            }
            catch (std::string error)
            {
                return false;
            }
        
    }

    bool Delete(std::string kxy, std::string path, std::string name)
    {
        std::map<std::string, RES> output;
        std::map<std::string, RES> gp = this->gen_tok(path);
        for (std::map<std::string, RES>::iterator it = gp.begin(); it != gp.end(); ++it)
        {
            if (it->first == kxy)
            {
            }
            else
            {
                output[it->first] = it->second;
            }
        }
        try
        {
            this->CreateSetBackUse(name, output);
            return true;
        }
        catch (std::string error)
        {
            return false;
        }
    }
    std::map<std::string, RES> search(std::string path, std::string kxy)
    {
        RES s;
        s.arr[0] = "success";
        RES f;
        f.arr[0] = "faliure";
        std::map<std::string, RES> output;
        std::map<std::string, RES> kv = this->gen_tok(path);
        for (std::map<std::string, RES>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            if (it->first == kxy)
            {
                output[it->first] = it->second;
                output["ret-val"] = s;
                return output;
            }
            //     std::cout << it->first + "-" + it->second << std::endl;
        }
        output["ret-val"] = f;
        return output;
    }
    bool CreateSetBackUse(std::string Set_name, std::map<std::string, RES> kv)
    {
        std::ofstream File("./Database/" + Set_name, std::ofstream::out | std::ofstream::trunc);
        Sanitizer sz = Sanitizer();
        std::string tempc = "";

        for (std::map<std::string, RES>::iterator it = kv.begin(); it != kv.end(); ++it)
        {
            for (int i = 0; i < 100; i++)
            {
                try
                {
                    if (it->second.arr[i] == "myendboi")
                    {
                        break;
                    }
                    else
                    {
                        tempc = tempc + it->second.arr[i] + ",";

                        //     std::cout<<it->second.arr[i]<<std::endl;
                    }
                }
                catch (std::string e)
                {
                    break;
                }
            }
            //  std::cout << tempc << std::endl;

            File << it->first + ":" + tempc + ";" + "\n";
            tempc = "";
        }
        File.close();
    }

    std::map<std::string, RES> gen_tok(std::string path)
    {
        Helpers hp = Helpers();
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
        char cg = ',';
        char c = ':';
        std::map<std::string, RES> kv;
        std::string result;

        while (text.length() > this->curr_l)
        {
            if (text[this->curr_l] == c)
            {
                // this->advance();

                this->advance();
                std::string temp;
                RES r;
                int pos = 0;
                while (text[this->curr_l] != s)
                {
                    if (text[this->curr_l] == cg)
                    {
                        r.arr[pos] = hp.delcomma(temp);
                        temp = "";
                        pos++;
                    }

                    temp = temp + text[this->curr_l];
                    this->advance();
                }
                r.arr[pos] = "myendboi";
                kv[result] = r;
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
        //  for (std::map<std::string, std::string>::iterator it = kv.begin(); it != kv.end(); ++it)
        //  {
        //        std::cout << it->first + "-" + it->second << std::endl;
        //       }

        return kv;
    }
};

class Database
{
  public:
    // Settings set;
    std::string path;
    static int counter;

    Database()
    {
        //this->set = s;
        //  this->path = this->set.path;
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
            //

            File << it->first + ":" + it->second + ",;" + "\n";
        }
        File.close();
    }

    std::map<std::string, RES> getMap(std::string filepath)
    {
        Lexer lx = Lexer();
        std::map<std::string, RES> output = lx.gen_tok(filepath);
        return output;

        // std::cout<<content<<std::endl;
    }
    std::map<std::string, RES> search(std::string key, std::string filepath)
    {
        Lexer lx = Lexer();
        std::map<std::string, RES> output = lx.search(filepath, key);

        return output;
    }
};

int main()
{
    std::string name = "Users";
    Database db = Database();
    //  db.MKDB();
    Lexer lx = Lexer();
    Helpers hp = Helpers();

    std::map<std::string, RES> kd;
    RES r;
    r.arr[0] = "shivansh";
    r.arr[1] = "cannon";
    r.arr[2] = "myendboi";
    RES b;
    b.arr[0] = "none";
    b.arr[1] = "alone";
    b.arr[2] = "learner";
    b.arr[3] = "myendboi";

    kd["name"] = r;
    kd["behaviour"] = b;
    lx.CreateSetBackUse("SUCCESS", kd);

    
    std::map<std::string, RES> ot = db.getMap("./Database/SUCCESS");
    std::cout << ot["name"].arr[0];
    //std::cout << gt["name"].arr[0];
    //lx.Delete("behaviour", "./Database/SUCCESS", "SUCCESS");
    RES f;
    f.arr[0]="bitch";
    f.arr[1]="trebapp";
    f.arr[2]="myendboi";
    lx.Update("behaviour",f,"./Database/SUCCESS", "SUCCESS");

    
}
