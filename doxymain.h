/*! \mainpage Documentation for \<stxxl\> library
 *
 *  \image html logo.png
 *
 * <BR><BR>
 * The core of \c \<stxxl\> is an implementation of the C++
 * standard template library STL for external memory (out-of-core)
 * computations, i.e., \c \<stxxl\> implements containers and algorithms
 * that can process huge volumes of data that only fit on 
 * disks. While the compatibility to the STL supports
 * ease of use and compatibility with existing applications,
 * another design priority is high performance. 
 * Here is a selection of \c \<stxxl\> performance features:
 * - transparent support of multiple disks
 * - variable block lengths
 * - overlapping of I/O and computation
 * - prevention of OS file buffering overhead
 *
 * \section platforms Platforms supported
 * Linux (kernel >= 2.4.18)
 *
 * \section current Current version
 * prerelease 0.2 contains a first implementation of the lower layers
 * (memory management, disk virtualization, prefetching,...).
 * From the higher layers, sorting and basic containers
 * (vectors, stacks) are supported.
 * Currently that sums to about 8000 lines of code.
 *
 * \section soon Coming soon
 * Priority queues and search trees (B+ trees) are the main nontrivial algorithms
 * missing from a complete implementation of STL. 
 * We are also working on a first expansion of STL that allows
 * pipelining several simple algorithms (sorting, filtering,...)
 * to minimize I/O volume. We will also soon have several nontrivial
 * example applications (minimum spanning trees, suffix array construction).
 *
 * Questions concerning use and development of the \c \<stxxl\> library mail to Roman
 *  Dementiev <A href='mailto:dementiev@mpi-sb.mpg.de'>dementiev@mpi-sb.mpg.de</A>.
 *
 * \link installation Installation \endlink
 *
 */


/*!
 * \page installation Installation
 *
 * \section download Download
 *
 * - Download gzipped tar ball from <A href="http://www.mpi-sb.mpg.de/~rdementi/files/stxxl.tgz">here</A>. 
 * - Unpack in some directory executing: \c tar \c zfxv \c stxxl.tgz ,
 * - Change to \c stxxl directory: \c cd \c stxxl ,
 * - Change file \c compiler.make according to your system configuration
 *   - name of your make program
 *   - name of your compiler
 *   - \c \<stxxl\> root directory ( \c directory_where_you_unpacked_the_tar_ball/stxxl )
 * - Run: \c make \c lib
 * - Run: \c make \c tests (optional, if you want to run some test programs)
 * 
 * In your makefiles of programs that will use \c \<stxxl\> you should include the file \c compiler.make
 * file (add the line 'include ../compiler.make') because it contains a useful variable (STXXL_VARS) 
 * that includes all compiler definitions and library paths that you need to compile an \c \<stxxl\> program.
 *
 * Before you try to run one of the \c \<stxxl\> examples (or your \c \<stxxl\> program) you must configure the disk 
 * space that will be used as external memory for the library. See next section.
 *
 * \section space Disk space
 *
 * To get best performance with \c \<stxxl\>  you should assign separate disks to it. 
 * These disks should be used by the library only.
 * Since \c \<stxxl\> is developed to exploit disk parallelism, the performance of your 
 * external memory application will increase if you use more than one disk. 
 * But from how many disks your application can benefit depends on how "I/O bound" it is.
 * With modern disk bandwidths
 * about of 40-60 MB/s most of applications are I/O bound for one disk. This means that if you add another disk
 * the running time will be halved. Adding more disks might also increase performance significantly.
 *
 * \section filesystem Recommended file system
 * 
 * Our library take benefit of direct user memory - disk transfers (direct access) which avoids 
 * superfluous copies. This method has some disadvantages when accessing files on \c ext2 partitions. 
 * Namely one requires one byte of internal memory per each accessed kilobyte of file space. For external 
 * memory applications with large inputs this could be not proper. Therefore we recommend to use the 
 * \c xfs file system <A href="http://oss.sgi.com/projects/xfs/">link</A> which does not have this overhead but
 * gives the same read and write performance. Note that file creation speed of \c xfs is slow, so that disk
 * files must be precreated.
 * 
 * \section configuration Disk configuration file
 * 
 * You must define the disk configuration for an \c \<stxxl\> program in a file named \c '.stxxl' that must reside 
 * in the same directory where you execute the program. You can change the default file name for the configuration 
 * file by setting the enviroment variable \c STXXLCFG . 
 * 
 *
 * Each line of the configuration file describes a disk. 
 * A disk description uses the following format:<BR>
 * \c disk=full_disk_filename,capacity,access_method
 *
 * Description of the parameters:
 * - \c full_disk_filename : full disk filename. In order to access disks \<stxxl\> uses file 
 * access methods. Each disk is respresented as a file. If you have a disk that is mapped in unix
 * to the path /mnt/disk0/, then the correct value for the \c full_disk_filename would be
 * \c /mnt/disk0/some_file_name ,
 * - \c capacity : maximum capacity of the disk in megabytes
 * - \c access_method : \c \<stxxl\> has a number of different file access implementations, choose one of them:
 *   - \c syscall uses \c read and \c write system calls which perform disk transfers directly 
 *   on user memory pages without superfluous copy (currently the fastest method)
 *   - \c mmap : performs disks transfers using \c mmap and \c munmap system calls
 *   - \c simdisk : simulates timings of the IBM IC35L080AVVA07 disk, full_disk_filename must point 
 *     to a file on a RAM disk partition with sufficient space
 *
 *
 * See also example configuration file \c 'stxxl/config_example' included into the tarball.
 * 
 * \section excreation Formatting external memory files
 *
 * In order to get the maximum performance one should format disk files described in the configuration file,
 * before running \c \<stxxl\> applications.
 *
 * The format utility is included into a set of \c \<stxxl\> utilities ( \c utils/createdisks ). Run this utility
 * for each disk described in your disk configuration file.
 *
 * 
 * */
