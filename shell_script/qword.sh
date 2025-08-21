#!/bin/bash/


# get user's string that needs to be searched

echo "Enter a search string:"
read search_string

#构造URL, 用jq工具确保字符串被正确URL编码.
url="https://www.quword.com/w/?q=$(echo $search_string | jq -sRr @uri)"

# send HTTP request, save the result as a html file.
output_file="search_result.html"
curl -o $output_file "$url"


echo "search results saved to $output_file"
