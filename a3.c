#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdbool.h>

// shared memory data
int fdShm = 0;
char *shared_memory = NULL;
unsigned int sizeOfShm = 0;

// mapped file data
int fdFile = 0;
char *mapped_file = NULL;
int sizeOfFile = 0;


// FUNCTIONS USED TO WRITE ERROR/SUCCESS ON PIPE FOR EACH REQUIREMENT

void create_shm_write_success(int fdResp){
    unsigned char size =10;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "CREATE_SHM", size) < 0){
        printf("error writing CREATE_SHM");
    }
    size = 7;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "SUCCESS", size) < 0){
        printf("error writing SUCCESS");
    }
}


void create_shm_write_error(int fdResp){
    unsigned char size =10;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "CREATE_SHM", size) < 0){
        printf("error writing CREATE_SHM");
    }
    size = 5;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "ERROR", size) < 0){
        printf("error writing ERROR");
    }      
}


void write_to_shm_write_success(int fdResp){
    unsigned char size =12;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "WRITE_TO_SHM", size) < 0){
        printf("error writing WRITE_TO_SHM");
    }
    size = 7;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "SUCCESS", size) < 0){
        printf("error writing SUCCESS");
    }
}


void write_to_shm_write_error(int fdResp){
    unsigned char size =12;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "WRITE_TO_SHM", size) < 0){
        printf("error writing WRITE_TO_SHM");
    }
    size = 5;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "ERROR", size) < 0){
        printf("error writing ERROR");
    }      
}


void map_file_write_success(int fdResp){
    unsigned char size = 8;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "MAP_FILE", size) < 0){
        printf("error writing MAP_FILE");
    }
    size = 7;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "SUCCESS", size) < 0){
        printf("error writing SUCCESS");
    }      
}


void map_file_write_error(int fdResp){
    unsigned char size = 8;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "MAP_FILE", size) < 0){
        printf("error writing MAP_FILE");
    }
    size = 5;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "ERROR", size) < 0){
        printf("error writing ERROR");
    }      
}


void read_from_file_offset_write_success(int fdResp){
    unsigned char size = 21;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "READ_FROM_FILE_OFFSET", size) < 0){
        printf("error writing READ_FROM_FILE_OFFSET");
    }
    size = 7;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "SUCCESS", size) < 0){
        printf("error writing SUCCESS");
    }      
}


void read_from_file_offset_write_error(int fdResp){
    unsigned char size = 21;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "READ_FROM_FILE_OFFSET", size) < 0){
        printf("error writing READ_FROM_FILE_OFFSET");
    }
    size = 5;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "ERROR", size) < 0){
        printf("error writing ERROR");
    }      
}


void read_from_file_section_write_success(int fdResp){
    unsigned char size = 22;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "READ_FROM_FILE_SECTION", size) < 0){
        printf("error writing READ_FROM_FILE_SECTION");
    }
    size = 7;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "SUCCESS", size) < 0){
        printf("error writing SUCCESS");
    }      
}


void read_from_file_section_write_error(int fdResp){
    unsigned char size = 22;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "READ_FROM_FILE_SECTION", size) < 0){
        printf("error writing READ_FROM_FILE_SECTION");
    }
    size = 5;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "ERROR", size) < 0){
        printf("error writing ERROR");
    }      
}


void read_from_logical_space_offset_write_success(int fdResp){
    unsigned char size = 30;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "READ_FROM_LOGICAL_SPACE_OFFSET", size) < 0){
        printf("error writing READ_FROM_LOGICAL_SPACE_OFFSET");
    }
    size = 7;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "SUCCESS", size) < 0){
        printf("error writing SUCCESS");
    }      
}


void read_from_logical_space_offset_write_error(int fdResp){
    unsigned char size = 30;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "READ_FROM_LOGICAL_SPACE_OFFSET", size) < 0){
        printf("error writing READ_FROM_LOGICAL_SPACE_OFFSET");
    }
    size = 5;
    if(write(fdResp, &size, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "ERROR", size) < 0){
        printf("error writing ERROR");
    }      
}


// FUNCTIONS USED TO IMPLEMENT THE ASSIGNMENT'S REQUIREMENTS


void pingpong(int fdResp, int fdReq){

    // write PING PONG 12741 on the response pipe
    unsigned char size1 = 4;
    unsigned int nr = 12741;
    if(write(fdResp, &size1, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "PING", size1) < 0){
        printf("error writing PING");
    }
    if(write(fdResp, &size1, 1) < 0){
        printf("error writing size");
    }
    if(write(fdResp, "PONG", size1) < 0){
        printf("error writing PONG");
    }
    if(write(fdResp, &nr, sizeof(unsigned int)) < 0){
        printf("error writing nr");
    }
            
}


void create_shm(int fdResp, int fdReq){
    read(fdReq, &sizeOfShm, sizeof(unsigned int));
    
    fdShm = shm_open("/ox92X7AZ", O_CREAT | O_RDWR, 0664);
    if(fdShm < 0) {
        create_shm_write_error(fdResp);
        return;
    }

    ftruncate(fdShm, sizeOfShm);

    shared_memory = (char*)mmap(NULL, sizeOfShm, PROT_READ | PROT_WRITE, MAP_SHARED, fdShm, 0);
        
    if(shared_memory == MAP_FAILED){
        create_shm_write_error(fdResp);
    }
    else create_shm_write_success(fdResp);
}


void write_to_shm(int fdResp, int fdReq){
    // read the value which must be written at index offset
    unsigned int offset;
    read(fdReq, &offset, sizeof(unsigned int));
    unsigned int value;
    read(fdReq, &value, sizeof(unsigned int));

    if(0 <= offset && offset < sizeOfShm){ // if offset is in range 0 <-> size of the shared memory
        if( (sizeof(value) + offset) <= sizeOfShm){ // if writting the value does not exceed the size of the shared memory      
            int* data = (int*) (shared_memory + offset); // cast the value of shared_memory[offset] to int because int has 4 bytes
            *data = value; // write the value on that position
            write_to_shm_write_success(fdResp);
        }
        else write_to_shm_write_error(fdResp);
    }
    else write_to_shm_write_error(fdResp);   
}


void map_file(int fdResp, int fdReq){
    // read the size of the string and then the string representing the file
    unsigned char sizeOfString;
    read(fdReq, &sizeOfString, 1);

    char* stringFile =(char*)malloc(sizeof(char)*sizeOfString);
    read(fdReq,stringFile,sizeOfString);
    stringFile[sizeOfString] = '\0';

    fdFile = open(stringFile, O_RDONLY);
    if(fdFile == -1) {
        map_file_write_error(fdResp);
        return;
    }

    // compute the size of the file using system calls
    sizeOfFile = lseek(fdFile, 0, SEEK_END);
    lseek(fdFile, 0, SEEK_SET);

    mapped_file = (char*)mmap(NULL, sizeOfFile, PROT_READ, MAP_SHARED, fdFile, 0);
    if(mapped_file == (void*)-1) {
        map_file_write_error(fdResp);
    }
    else{
        map_file_write_success(fdResp);
    }
}


void read_from_file_offset(int fdResp, int fdReq){
    // read the offset and the number of bytes
    unsigned int offset;
    read(fdReq, &offset, sizeof(unsigned int));
    unsigned int no_of_bytes;
    read(fdReq, &no_of_bytes, sizeof(unsigned int));           

    if(shared_memory != MAP_FAILED){ // if there exists a shared memory
        if(mapped_file != (void*)-1) { // if there exists a mapped file
            if(( offset + no_of_bytes) <= sizeOfFile){  // if reading no_of_bytes from position offset does not exceed the size of the file   

                for(int i = offset; i <= offset+no_of_bytes; i++){
                    shared_memory[i-offset] = mapped_file[i];
                }

                read_from_file_offset_write_success(fdResp);
            }
            else read_from_file_offset_write_error(fdResp);
        }
        else read_from_file_offset_write_error(fdResp);
    }  
    else read_from_file_offset_write_error(fdResp);         
}


void read_from_file_section(int fdResp, int fdReq){
    // read from the request pipe the number of the section, the offset from which we start the reading and the number of bytes we read
    unsigned int section_no;
    read(fdReq, &section_no, sizeof(unsigned int));
    unsigned int offset;
    read(fdReq, &offset, sizeof(unsigned int));
    unsigned int no_of_bytes;
    read(fdReq, &no_of_bytes, sizeof(unsigned int));

    int no_of_sections =  (int) mapped_file[7]; // read from the mapped file the number of sections the SF file has

    if(0 < section_no && section_no <= no_of_sections){ // if the given section number is in range 0 <-> no_of_sections

        int section_header = 10 + 1 + 4 + 4; // == number of bytes (or size) of each section
        int jumpToSection = 8 + section_header * (section_no - 1) ; // compute the address where section_no starts
        // 8 = number of bytes before the section headers (=magic, version, no_of_sections,header_size)
        // + the size of a section * number of sections before the section_no section
        
        int index = jumpToSection + 11; // the address where sect_offset is in section_no section
        // 11 = the number of bytes from the section before sect_offset (sect_name, sect_type)

        char * offsetAddress = &mapped_file[index]; // get the value of sect_offset from the section_no section
        unsigned int sect_offset = *(unsigned int*)offsetAddress;

        for(index = sect_offset + offset; index <= sect_offset + offset + no_of_bytes; index++){
            shared_memory[index - sect_offset - offset] = mapped_file[index];
        }    
        read_from_file_section_write_success(fdResp);    
    }
    else read_from_file_section_write_error(fdResp);
}


int getNextMultiple(int index){
    if(index == 0){ // first section starts at 0
        return 0;
    }
    else{
        return ((index/4096) + 1) * 4096; // divide index by 4096 to get the previous section_no and add 1 to get to the next multiple of 4096
    }
}


void read_from_logical_space_offset(int fdResp, int fdReq){
    // read the logical offset and the number of bytes
    unsigned int logical_offset;
    read(fdReq, &logical_offset, sizeof(unsigned int));
    unsigned int no_of_bytes;
    read(fdReq, &no_of_bytes, sizeof(unsigned int));

    int no_of_sections =  (int) mapped_file[7]; // = number of sections in the SF file
    
    int section_header = 10 + 1 + 4 + 4; // = size of a section in the header
    unsigned int sect_size = 0;
    unsigned int sect_offset = 0;
    char * sizeAddress;

    int index = 0; // = index in the logical memory space
    int section_no; // = the number of the section in which logical_offset is
    int offset; // = the value of the logical_offset in the section from the SF file
    
    int* startIndexVector = (int*)malloc(sizeof(int) * no_of_sections); // = an array in which we keep all start indexes in the logical memory space for each section

    for(int iterator = 1; iterator <= no_of_sections; iterator++){

        int multiple = getNextMultiple(index); // get next multiple of 4096
        startIndexVector[iterator] = multiple; // section "iterator" will start in the logical memory space at position "multiple"
        
        int i = 8 + section_header *(iterator - 1) + 15; // compute the address of sect_size of section "iterator" in the header of the SF file
        sizeAddress = &mapped_file[i]; // get the value of sect_size from the "iterator" section
        sect_size = *(unsigned int*)sizeAddress;

        index = multiple + sect_size; // the new index in the logical memory space
    }

   
    for(int iterator = 1; iterator <= no_of_sections; iterator++){   
        // check if the logical offset is in the last section
        // check if the logical offset is in between the current and the next value of the index in the logical memory space
        // if so, then logical_offset is in the "iterator" section 
        if((iterator==no_of_sections && logical_offset>=startIndexVector[iterator]) || (startIndexVector[iterator]<=logical_offset && logical_offset<=startIndexVector[iterator+1])){
            section_no = iterator; // get the section number
            offset = logical_offset - startIndexVector[iterator]; // get the value of the logical_offset in the section in the SF file

            int i = 8 + section_header *(section_no - 1) + 15;
            sizeAddress = &mapped_file[i]; // get the value of sect_size of the section_no section
            sect_size = *(unsigned int*)sizeAddress;

            int j = 8 + section_header *(section_no - 1) + 11;
            sizeAddress = &mapped_file[j]; // get the value of sect_offset of the section_no section
            sect_offset = *(unsigned int*)sizeAddress;

            break;
        }
       
    }
    // check if the offset does not exceed the size of the section
    // check if reading no_of_bytes does not exceed the size of the section
    if(offset <= sect_size && (offset + no_of_bytes) <= sect_size){
        for(index = sect_offset + offset; index <= sect_offset + offset + no_of_bytes; index++){
            shared_memory[index - sect_offset - offset] = mapped_file[index];
        }    
        read_from_logical_space_offset_write_success(fdResp);
    }
    else{
        read_from_logical_space_offset_write_error(fdResp);
    }
}


int main(int argc, char** argv){

    // create the response pipe
    mkfifo("RESP_PIPE_12741", 0700);

    // open the request pipe
    int fdReq = open("REQ_PIPE_12741", O_RDONLY);

    if(fdReq < 0){
        printf("ERROR\ncannot open the request pipe\n");
        return -1;
    }

    // open the response pipe
    int fdResp = open("RESP_PIPE_12741", O_WRONLY);

    if(fdResp<0){
        printf("ERROR\ncannot create the response pipe\n");
        return -1;
    }       

    // write CONNECT on the response pipe
    unsigned char sizeConnect = 7;   
    write(fdResp, &sizeConnect, 1);   
    if(write(fdResp, "CONNECT", sizeConnect) != -1){
        printf("SUCCESS\n");
    }    

    while(1){
        // read the size of the string and then read the string representing the next command
        unsigned char size;
        read(fdReq, &size, 1);

        char* buf=(char*)malloc(sizeof(char)*size);
        read(fdReq,buf,size);
        buf[size] = '\0';

        if(strcmp(buf,"PING") == 0){
           pingpong(fdResp, fdReq);
        }         
        else if(strcmp(buf,"CREATE_SHM")==0){
            create_shm(fdResp, fdReq);        
        }
        else if(strcmp(buf,"WRITE_TO_SHM") == 0){
            write_to_shm(fdResp, fdReq);
        }
        else if(strcmp(buf,"MAP_FILE") == 0){
            map_file(fdResp, fdReq);
        }
        else if(strcmp(buf,"READ_FROM_FILE_OFFSET") == 0){
            read_from_file_offset(fdResp, fdReq);
        }
        else if(strcmp(buf,"READ_FROM_FILE_SECTION") == 0){
            read_from_file_section(fdResp, fdReq);
        }
        else if(strcmp(buf,"READ_FROM_LOGICAL_SPACE_OFFSET") == 0){
            read_from_logical_space_offset(fdResp, fdReq);
        }       
        else if(strcmp(buf, "EXIT") == 0){
            close(fdResp);
            close(fdReq);
            unlink("RESP_PIPE_12741");
            munmap(shared_memory, sizeOfShm);
            munmap(mapped_file, sizeOfFile);
            break;                  
        }  
    }

}