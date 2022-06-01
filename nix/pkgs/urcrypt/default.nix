{ stdenv, autoreconfHook, pkgconfig
, libaes_siv, openssl, secp256k1, libecc
, enableStatic ? stdenv.hostPlatform.isStatic }:

stdenv.mkDerivation rec {
  name = "urcrypt";
  src  = ../../../pkg/urcrypt;

  # XX why are these required for darwin?
  dontDisableStatic = enableStatic;

  configureFlags = if enableStatic
    then [ "--disable-shared" "--enable-static" ]
    else [];

#  configurePhase = ''
#    ./configure
#    echo "runing configure"
#    declare -p
#    ./configure --disable-silent-rules
#  '';

  nativeBuildInputs =
    [ autoreconfHook pkgconfig ];

  propagatedBuildInputs =
    [ openssl secp256k1 libaes_siv ];

  buildInputs = [ libecc ];

  #buildFlags = [ "WITH_STDLIB=1" ];

  #preBuildPhases = [ blahPhase ];

#  blahPhase = ''
#    export NIX_CFLAGS_COMPILE="-DWITH_STDLIB" # needed for libecc
#  '';

#buildPhase = ''
#    declare -p
#    make
#  '';

  #installPhase = ''
    #echo hello 
    #ls ${libecc}
    #declare
  #'';


}
