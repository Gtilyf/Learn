# Jetty & LOCAL of Linux

- ssh sendEnv

- LC_CTYPE
  
  > LC_CTYPE
  > 
  > **This variable determines the locale category for character handling functions**, such as *tolower()*, *toupper()* and *isalpha()*. This environment variable determines the interpretation of sequences of bytes of text data as characters (for example, single- as opposed to multi-byte characters), the classification of characters (for example, alpha, digit, graph) and the behaviour of character classes. Additional semantics of this variable, if any, are implementation-dependent.

- locale
  
  > LC_ALL > LC_* >LANG 

- `JAVA_OPTIONS+=("-Dfile.encoding=UTF-8")`

- sun.jnu.encoding & file.encoding
  
  - sun.jnu.encoding (LANG)，影响文件命名
  - file.encoding (LC_CTYPE)，影响文件内容

- **java_props_md.c**
  
  ​
