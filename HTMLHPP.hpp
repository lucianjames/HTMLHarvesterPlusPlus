#include <string>
#include <vector>


namespace HTMLH {

    namespace internal{

        std::vector<std::string> linkTags = {"href","src"};

    }

    std::string getTitle(std::string& html){ // ! html passed by reference for increased performance, but dont modify it !
        size_t pos = html.find("<title>") + 7;
        size_t endpos = html.find("</title>");
        if(pos == std::string::npos){
            return "Title not found"; // Bad err handling
        }
        if(endpos == std::string::npos){
            return "End of title not found"; // Bad err handling
        }
        std::string title = html.substr(pos, endpos-pos);
        return title;
    }

    std::vector<std::string> getLinks(std::string& html){ // ! html passed by reference for increased performance, but dont modify it !
        std::vector<std::string> links;
        for(std::string tag : internal::linkTags){ // internal::linkTags contains a list of "tags" that specify links (src, href, etc)
            size_t found = html.find(tag, 0); // Find the first tag
            size_t tagFindStart = 0; // Used to find the next tag (updates to position of end of current link)
            while(found != std::string::npos){
                size_t firstQuote = html.find('"', found) + 1;
                size_t secondQuote = html.find('"', firstQuote+1);    
                if(firstQuote == std::string::npos || secondQuote == std::string::npos){
                    break;
                }
                links.push_back(html.substr(firstQuote, secondQuote-firstQuote));

                // Find the next tag
                tagFindStart = secondQuote + 1;
                found = html.find(tag, tagFindStart);
            }
        }
        return links;
    }

}