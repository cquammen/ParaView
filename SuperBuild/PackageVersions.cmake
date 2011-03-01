
set(PYTHON_MAJOR 2)
set(PYTHON_MINOR 7)
set(PYTHON_PATCH 1)
set(PYTHON_VERSION ${PYTHON_MAJOR}.${PYTHON_MINOR}.${PYTHON_PATCH})
set(PYTHON_URL http://python.org/ftp/python/${PYTHON_MAJOR}.${PYTHON_MINOR})
set(PYTHON_GZ Python-${PYTHON_MAJOR}.${PYTHON_MINOR}.tgz)
set(PYTHON_MD5 35f56b092ecf39a6bd59d64f142aae0f)

set(PYVER ${PYTHON_MAJOR}.${PYTHON_MINOR})
set(PYVER_SHORT ${PYTHON_MAJOR}${PYTHON_MINOR})

set(SIP_MAJOR 4)
set(SIP_MINOR 12)
set(SIP_PATCH 1)
set(SIP_VERSION ${SIP_MAJOR}.${SIP_MINOR}.${SIP_PATCH})
set(SIP_URL http://www.riverbankcomputing.co.uk/static/Downloads/sip4)
set(SIP_GZ sip-${SIP_VERSION}.tar.gz)
set(SIP_MD5 0f8e8305b14c1812191de2e0ee22fea9)

set(PYQT_MAJOR 4)
set(PYQT_MINOR 8)
set(PYQT_PATCH 3)
set(PYQT_VERSION ${PYQT_MAJOR}.${PYQT_MINOR}.${PYQT_PATCH})
set(PYQT_URL http://www.riverbankcomputing.co.uk/static/Downloads/PyQt4)
set(PYQT_GZ PyQt-x11-gpl-${PYQT_VERSION}.tar.gz)
set(PYQT_MD5 d54fd1c37a74864faf42709c8102f254)

set(NUMPY_MAJOR 1)
set(NUMPY_MINOR 5)
set(NUMPY_PATCH 1)
set(NUMPY_URL http://downloads.sourceforge.net/project/numpy/NumPy/${NUMPY_MAJOR}.${NUMPY_MINOR}.${NUMPY_PATCH})
set(NUMPY_GZ numpy-${NUMPY_MAJOR}.${NUMPY_MINOR}.${NUMPY_PATCH}.tar.gz)
set(NUMPY_MD5 376ef150df41b5353944ab742145352d)

set(BLAS_URL http://www.netlib.org/blas)
set(BLAS_GZ blas.tgz)

set(BOOST_MAJOR 1)
set(BOOST_MINOR 41)
set(BOOST_PATCH 0)
set(BOOST_VERSION ${BOOST_MAJOR}.${BOOST_MINOR}.${BOOST_PATCH})
set(BOOST_URL http://www.vtk.org/files/support)
set(BOOST_GZ boost-${BOOST_VERSION}.cmake-kitware.tar.gz)
set(BOOST_MD5 f09997a2dad36627579b3e2215c25a48)

set(LAPACK_MAJOR 3)
set(LAPACK_MINOR 2)
set(LAPACK_PATCH 1)
set(LAPACK_VERSION ${LAPACK_MAJOR}.${LAPACK_MINOR}.${LAPACK_PATCH})
set(LAPACK_URL http://www.netlib.org/lapack)
set(LAPACK_GZ lapack-${LAPACK_VERSION}-CMAKE.tgz)
set(LAPACK_MD5 71ce47837af7d3ba44aa04c6e74e53ff)

set(CLAPACK_MAJOR 3)
set(CLAPACK_MINOR 2)
set(CLAPACK_PATCH 1)
set(CLAPACK_VERSION ${CLAPACK_MAJOR}.${CLAPACK_MINOR}.${CLAPACK_PATCH})
set(CLAPACK_URL http://www.netlib.org/clapack)
set(CLAPACK_GZ clapack-${CLAPACK_VERSION}-CMAKE.tgz)
set(CLAPACK_MD5 4fd18eb33f3ff8c5d65a7d43913d661b)

set(FFMPEG_MAJOR 0)
set(FFMPEG_MINOR 6)
set(FFMPEG_PATCH 1)
set(FFMPEG_URL http://ffmpeg.org/releases)
set(FFMPEG_GZ ffmpeg-${FFMPEG_MAJOR}.${FFMPEG_MINOR}.${FFMPEG_PATCH}.tar.gz)
set(FFMPEG_MD5)

if(WIN32)
  set(MANTA_REVISION 2478)
  set(MANTA_MD5 1e0fa4dde2815a0977a93d09cce40d74)
else()
  set(MANTA_REVISION 2439)
  set(MANTA_MD5 43e05498964a826360de38cc3008c02d)
endif()
set(MANTA_URL http://paraview.org/files/misc)
set(MANTA_GZ manta-r${MANTA_REVISION}.tar.gz)

set(OPENMPI_MAJOR 1)
set(OPENMPI_MINOR 4)
set(OPENMPI_PATCH 3)
set(OPENMPI_VERSION ${OPENMPI_MAJOR}.${OPENMPI_MINOR}.${OPENMPI_PATCH})
set(OPENMPI_URL http://www.open-mpi.org/software/ompi/v${OPENMPI_MAJOR}.${OPENMPI_MINOR}/downloads)
set(OPENMPI_GZ openmpi-${OPENMPI_VERSION}.tar.gz)
set(OPENMPI_MD5 e7148df2fe5de3e485838bfc94734d6f)

set(MPICH2_MAJOR 1)
set(MPICH2_MINOR 3)
set(MPICH2_PATCH 1)
set(MPICH2_VERSION ${MPICH2_MAJOR}.${MPICH2_MINOR}.${MPICH2_PATCH})
set(MPICH2_URL http://www.mcs.anl.gov/research/projects/mpich2/downloads/tarballs/${MPICH2_VERSION})
set(MPICH2_GZ mpich2-${MPICH2_VERSION}.tar.gz)
set(MPICH2_MD5 eced41738eca4762b020e5521bb8c53d)

set(QT_MAJOR 4)
set(QT_MINOR 6)
set(QT_PATCH 3)
set(QT_VERSION ${QT_MAJOR}.${QT_MINOR}.${QT_PATCH})
set(QT_URL http://get.qt.nokia.com/qt/source)
set(QT_GZ qt-everywhere-opensource-src-${QT_VERSION}.tar.gz)
set(QT_MD5 6f88d96507c84e9fea5bf3a71ebeb6d7)

set(CGNS_MAJOR 2)
set(CGNS_MINOR 5)
set(CGNS_PATCH 5)
set(CGNS_VERSION ${CGNS_MAJOR}.${CGNS_MINOR}.${CGNS_PATCH})
set(CGNS_URL http://paraview.org/files/misc)
set(CGNS_GZ cgnslib_${CGNS_MAJOR}.${CGNS_MINOR}-${CGNS_PATCH}.tar.gz)
set(CGNS_MD5 ae2a2e79b99d41c63e5ed5f661f70fd9)

set(SILO_MAJOR 4)
set(SILO_MINOR 8)
set(SILO_PATCH 0)
set(SILO_VERSION ${SILO_MAJOR}.${SILO_MINOR}.${SILO_PATCH})
set(SILO_URL http://paraview.org/files/misc)
set(SILO_GZ silo-${SILO_MAJOR}.${SILO_MINOR}-bsd.tar.gz)
set(SILO_MD5 040d99a7b55be4e2e0bb765560d3137c)

set(HDF5_MAJOR 1)
set(HDF5_MINOR 8)
set(HDF5_PATCH 5-patch1)
set(HDF5_VERSION ${HDF5_MAJOR}.${HDF5_MINOR}.${HDF5_PATCH})
set(HDF5_URL http://www.hdfgroup.org/ftp/HDF5/prev-releases/hdf5-${HDF5_VERSION}/src)
set(HDF5_GZ hdf5-${HDF5_VERSION}.tar.gz)
set(HDF5_MD5 d22a35a17877e369055ed50da5ba91fa)

set(ZLIB_MAJOR 1)
set(ZLIB_MINOR 2)
set(ZLIB_PATCH 5)
set(ZLIB_VERSION ${ZLIB_MAJOR}.${ZLIB_MINOR}.${ZLIB_PATCH})
set(ZLIB_URL http://zlib.net)
set(ZLIB_GZ zlib-${ZLIB_VERSION}.tar.gz)
set(ZLIB_MD5 c735eab2d659a96e5a594c9e8541ad63)

set(PNG_MAJOR 1)
set(PNG_MINOR 5)
set(PNG_PATCH 1)
set(PNG_VERSION ${PNG_MAJOR}.${PNG_MINOR}.${PNG_PATCH})
set(PNG_URL ftp://ftp.simplesystems.org/pub/libpng/png/src)
set(PNG_GZ libpng-${PNG_VERSION}.tar.gz)
set(PNG_MD5 220035f111ea045a51e290906025e8b5)