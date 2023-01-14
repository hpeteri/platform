
FileContent read_entire_file(const char* file_path, n1_Allocator allocator){
  
  FileContent file_content = {0, 0};
  
  HANDLE file = CreateFile(file_path,
                           GENERIC_READ,
                           FILE_SHARE_READ,
                           NULL,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_READONLY,
                           NULL);

  if(file != INVALID_HANDLE_VALUE){
    LARGE_INTEGER size;
    GetFileSizeEx(file, &size);

    file_content.size = size.QuadPart + 1;
    file_content.data = allocator.alloc(file_content.size);

      
    ReadFile(file,
             file_content.data,
             file_content.size,
             NULL,
             NULL);
    
    CloseHandle(file);
  }

  return file_content;
}
