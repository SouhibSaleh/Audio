#include <iostream>
#include <string>
#include <sndfile.h>  
#include <fstream>

int main() {
    const char* filePath = "";  
    const char* file_to_write = "";

    SF_INFO sfInfo;
    sfInfo.format = 0;  

    SNDFILE* sndFile = sf_open(filePath, SFM_READ, &sfInfo);


    if (sndFile == nullptr) {
        std::cerr << "Error: Unable to open file: " << sf_strerror(sndFile) << std::endl;
        return 1;
    }

    long long number_of_samples = sfInfo.frames * sfInfo.channels;
    float* samples = new float[number_of_samples];
    sf_count_t samples_reader = sf_readf_float(sndFile,samples,sfInfo.frames);

    std::fstream stream(file_to_write, std::ios::out);
    if (!stream.is_open())
    {
        std::cerr << "Error: Unabale to open file" << std::endl;
        return 1;
    }
    for (int x = 0; x < number_of_samples; x++)
    {
        stream << x << " " << samples[x]<<std::endl;
    }
    
    delete []samples;
    stream.close();
    sf_close(sndFile);

    return 0;
}
