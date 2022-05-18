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

  nativeBuildInputs =
    [ autoreconfHook pkgconfig ];

  propagatedBuildInputs =
    [ openssl secp256k1 libaes_siv ];

  buildInputs = [ libecc ];

  installPhase = ''
    echo hello 
    pwd 
    ls ${libecc}
  '';

  shellHook = '' 
    LIBECC_LIBS="${libecc}
  ''

}
