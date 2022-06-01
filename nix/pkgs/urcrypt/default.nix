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

  configurePhase = ''
    echo "runing configure"
    declare -p
    ./configure --disable-silent-rules
  '';

  nativeBuildInputs =
    [ autoreconfHook pkgconfig ];

  propagatedBuildInputs =
    [ openssl secp256k1 libaes_siv ];

  buildInputs = [ libecc ];

  buildPhase = ''
    declare -F
    NIX_CFLAGS_COMPILE="-DWITH_STDLIB $NIX_CFLAGS_COMPILE" # needed for libecc
    make
  '';

  #installPhase = ''
    #echo hello 
    #ls ${libecc}
    #declare
  #'';


}
