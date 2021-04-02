#include "yellower.h"
#include <thread>
#include <deque>


#include <ctime>

int main()
{
    //get parameters from user

    std::string dir_path;   /*copy-pasted full path, tested on windows (eg.: Z:\pics\yellow\coloring )*/
    std::cout << "Please input the working directory:" << std::endl;
    std::cin >> dir_path;

    std::string target_hex; /*purely the number itself, without # */
    std::cout << "Please input the hex for recoloring:" << std::endl;
    std::cin >> target_hex;

    //remove # from target_hex if present
    if(target_hex[0]=='#'){
        target_hex = target_hex.substr(1);
    }

    float intensity;    /*integer between 0 and 100*/
    std::cout << "Please input the intensity:" << std::endl;
    std::cin >> intensity;

    //log starting time
    std::clock_t start = clock();

    //convert target_hex into rgb
    std::vector<unsigned char > target_rgb;
    target_rgb.push_back(stoi(target_hex.substr(0, 2), 0, 16));
    target_rgb.push_back(stoi(target_hex.substr(2, 2), 0, 16));
    target_rgb.push_back(stoi(target_hex.substr(4, 2), 0, 16));

    //create vector to handle threads
    std::deque<std::thread> threads;

    std::cout << "Collecting files" << std::endl;

    //iterate through the files in library from dir_path
    for(const auto& entry : fs::directory_iterator(dir_path)){
        std::string ext = entry.path().extension().string();

        if(ext == ".jpg" || ext == ".jpeg" || ext == ".png"){
            //set up thread, start processing with libjpeg
            threads.emplace_back(recolor, entry.path().string(), ext, intensity, target_rgb);
        } else{
            //log exception
            std::cout<<"weird";
        }

    }

    std::cout << "Starting recoloring" << std::endl;

    size_t i=0;
    size_t threads_original_length = threads.size();
    while (i<threads_original_length){
        threads[0].join();
        threads.pop_front();
        i++;
    }

    std::cout<<"Recoloring finished." << std::endl;

    //output the time diff between starting and finishing
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);


    return 0;
}
