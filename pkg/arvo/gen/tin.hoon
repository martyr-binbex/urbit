::  Produce a tin pill - a minimal pill with only a 
::  precompiled hoon compiler
::
::::  
  ::
/?    310
/+  pill
::
::::
  !:
:-  %say
|=  $:  [now=@da eny=@uvJ bec=beak]
      ::
        ::  arg: desks to build pill from
        ::
        ::
        ::    list of desks. defaults to [%base]~.
        ::    the first desk in this list will become the pill's base desk.
        ::    optionally, the first desk may be replaced with a fully
        ::    qualified path to the new boot system (typically in sys).
        ::    the rest of the desks will be installed through kiln.
        ::
        $=  arg
        $@  ~
        $:  base=$@(desk [@ta @ta @ta path])
            rest=(list desk)
        ==
      ::
        ~
    ==
~&  "running +tin"
:-  %boot-pill
^-  pill:pill
::  sys: root path to boot system, `/~me/[desk]/now/sys`
::  bas: root path to boot system' desk
::  dez: secondary desks and their root paths
::
=/  sys=path
  ?:  ?=([^ *] arg)
    `path`base.arg
  =/  =desk
    ?~  arg  %base
    ?>(?=(@ base.arg) base.arg)
  /(scot %p p.bec)/[desk]/(scot %da now)/sys
=/  bas=path
  (scag 3 sys)
=/  dez=(list [desk path])
  ?~  arg  ~
  %+  turn  rest.arg
  |=  =desk
  [desk /(scot %p p.bec)/[desk]/(scot %da now)]
::
::  compiler-source: hoon source file producing compiler, `sys/hoon`
::
=+  compiler-source=.^(@t %cx (welp sys /hoon/hoon))
::
::  compiler-twig: compiler as hoon expression
::
~&  %tin-parsing
=+  compiler-twig=(rain /sys/hoon/hoon compiler-source)
~&  %tin-parsed
::
::  compiler-formula: compiler as nock formula
::
~&  %tin-compiling
=+  compiler-formula=q:(~(mint ut %noun) %noun compiler-twig)
~&  %tin-compiled
::
::[%pill %tin ~[compiler-formula] ~ ~]
:+  %pill  %tin 
:+  ~[compiler-formula]  ~  ~