#include "yellower.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ExternalIncludeFiles/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ExternalIncludeFiles/stb_image_write.h"


//define thread functions
void recolor(const std::string imgpath, const std::string ext, float intensity, const std::vector<unsigned char>& target_rgb){
    //std::cout << "Starting " << imgpath << std::endl;
    //SET UP READ
    //init read result vars
    int width, height, component_number;
    //init loading image, result ptr
    unsigned char *image_in = stbi_load(imgpath.c_str(), &width, &height, &component_number, 4);

    //check if image_in is nullptr, showing that reading was invalid
    if(image_in== nullptr){
        std::cout << "Error while reading " << imgpath << " , reason: " << std::endl;
        std::cout << stbi_failure_reason()<<std::endl;
        return;
    }


    intensity /=100;

    //loop for each pixel component, recolor into results
    for(int i = 0; i<(width)*(height)*4;i++){
        if(i%4!=3) {
            //processes pixel unless it's from the 4th (alpha)
            //channel typecasts necessary to keep significant color data
            image_in[i] =  (unsigned char) round(abs(((float) image_in[i]) * (1 - intensity) + ((float)target_rgb[i%4]) * intensity));
        }
    }

    //SET UP WRITE
    //set up output address
    std::string img_out_path = imgpath;
    img_out_path.insert(imgpath.find_last_of('\\')+1, "recolor_");

    //choose output format, write output
    if(ext==".jpeg" || ext == ".jpg"){
        //output jpeg, returns 0 on failure
        if(stbi_write_jpg(img_out_path.c_str(), width, height, 4, image_in, 100)==0){
            std::cout << "Writing into " << img_out_path << " failed." << std::endl;
        }
    } else if(ext == ".png"){
        //output jpeg, returns 0 on failure
        if(stbi_write_png(img_out_path.c_str(), width, height, 4, image_in, 0)==0) {
            std::cout << "Writing into " << img_out_path << " failed." << std::endl;
        }
    }

    //free memory
    stbi_image_free(image_in);
    //std::cout << "Finishing " << imgpath << std::endl;
}