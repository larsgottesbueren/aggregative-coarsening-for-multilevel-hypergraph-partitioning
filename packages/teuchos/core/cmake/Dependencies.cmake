TRIBITS_PACKAGE_DEFINE_DEPENDENCIES(
  LIB_OPTIONAL_PACKAGES  KokkosCore
  LIB_OPTIONAL_TPLS  BinUtils  Boost  MPI  ARPREC  QD  QT  quadmath yaml-cpp
  )

TRIBITS_ALLOW_MISSING_EXTERNAL_PACKAGES(KokkosCore)
