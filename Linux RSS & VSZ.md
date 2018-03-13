# Linux RSS & VSZ

[What is RSS and VSZ in Linux memory management](https://stackoverflow.com/questions/7880784/what-is-rss-and-vsz-in-linux-memory-management)

> RSS is the Resident Set Size and is used to show how much memory is allocated to that process and is in RAM. It does not include memory that is swapped out. It does include memory from shared libraries as long as the pages from those libraries are actually in memory. It does include all stack and heap memory.
>
> VSZ is the Virtual Memory Size. It includes all memory that the process can access, including memory that is swapped out and memory that is from shared libraries.

