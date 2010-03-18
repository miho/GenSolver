Name:         gensolver  

%if %{defined suse_version}
BuildRequires: gcc-c++ cmake flexpars
Requires: flexpars
%endif

%if %{defined fedora_version} || 0%{?rhel_version} || 0%{?centos_version}
BuildRequires: gcc-c++ cmake
Requires: flexpars
%endif

%if %{defined mandriva_version}
BuildRequires: gcc-c++ cmake
Requires: flexpars
%endif

License:      LGPL  
Group:        System/Libraries
Summary:      Genetic algorithm with support for neural networks
BuildRoot:    %{_tmppath}/%{name}-%{version}-build  
URL:          http://github.com/miho/GenSolver
Version:      0.2-HEAD
Release:      0
Source:       %name-%{version}.tar.gz
  
%description  
GenSolver is a basic genetic algorithm. It is type and problem independent and includes support for neural networks.
   
   
   
Authors:  
--------  
     Michael Hoffer <info@michaelhoffer.de>  
   
%prep
%setup -q
  
%build 

cmake -DCMAKE_INSTALL_PREFIX=$RPM_BUILD_ROOT/usr .
make  
  
%install  
make install

%clean
# clean up the hard disc after build
rm -rf $RPM_BUILD_ROOT
  
%files
%defattr(-,root,root)
/usr/lib/gensolver/*
/usr/include/gensolver/*
