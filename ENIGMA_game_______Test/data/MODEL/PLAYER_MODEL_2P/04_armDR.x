xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 82;
 0.52847;0.44137;0.63450;,
 0.50107;-1.02867;-0.79409;,
 0.53360;0.42209;-1.40522;,
 0.48462;-1.61833;0.65386;,
 0.49386;-1.00139;2.09049;,
 0.52339;0.46065;2.67422;,
 0.55594;1.91143;2.06309;,
 0.57241;2.50109;0.61514;,
 0.56313;1.88415;-0.82149;,
 0.41006;-1.16744;-0.93100;,
 0.44567;0.42212;-1.60058;,
 0.39203;-1.81347;0.65549;,
 0.40215;-1.13755;2.22956;,
 0.43451;0.46436;2.86911;,
 0.47016;2.05393;2.19954;,
 0.48822;2.69999;0.61304;,
 0.47807;2.02406;-0.96103;,
 0.15620;-1.28129;-1.04757;,
 0.19446;0.42594;-1.76671;,
 0.13678;-1.97520;0.65638;,
 0.14768;-1.24923;2.34695;,
 0.18246;0.47133;3.03386;,
 0.22072;2.17855;2.31472;,
 0.24010;2.87238;0.61079;,
 0.22920;2.14644;-1.07980;,
 -0.22194;-1.35294;-1.12599;,
 -0.18192;0.43291;-1.87825;,
 -0.24226;-2.07879;0.65640;,
 -0.23087;-1.31938;2.42486;,
 -0.19453;0.48034;3.14338;,
 -0.15445;2.26620;2.39114;,
 -0.13417;2.99207;0.60873;,
 -0.14555;2.23265;-1.15970;,
 -0.66677;-1.37147;-1.15437;,
 -0.62612;0.44199;-1.91826;,
 -0.68735;-2.10851;0.65559;,
 -0.67578;-1.33739;2.45135;,
 -0.63887;0.49020;3.18100;,
 -0.59821;2.30363;2.41713;,
 -0.57762;3.04070;0.60715;,
 -0.58922;2.26953;-1.18861;,
 -9.95469;-1.17380;-1.17946;,
 -9.91405;0.63964;-1.94333;,
 -9.97526;-1.91085;0.63052;,
 -9.96370;-1.13973;2.42628;,
 -9.92677;0.68786;3.15593;,
 -9.88612;2.50133;2.39204;,
 -9.86556;3.23834;0.58209;,
 -9.87713;2.46722;-1.21367;,
 -10.39850;-1.13641;-1.15346;,
 -10.35844;0.64946;-1.90571;,
 -10.41873;-1.86219;0.62894;,
 -10.40737;-1.10282;2.39738;,
 -10.37100;0.69696;3.11592;,
 -10.33094;2.48282;2.36366;,
 -10.31069;3.20862;0.58127;,
 -10.32207;2.44924;-1.18718;,
 -10.77362;-1.04869;-1.07705;,
 -10.73537;0.65853;-1.79619;,
 -10.79300;-1.74256;0.62688;,
 -10.78213;-1.01661;2.31747;,
 -10.74738;0.70391;3.00438;,
 -10.70908;2.41116;2.28524;,
 -10.68972;3.10502;0.58128;,
 -10.70059;2.37907;-1.10928;,
 -11.02311;-0.92414;-0.96187;,
 -10.98746;0.66544;-1.63144;,
 -11.04113;-1.57018;0.62463;,
 -11.03102;-0.89425;2.19870;,
 -10.99862;0.70770;2.83825;,
 -10.96298;2.29730;2.16867;,
 -10.94493;2.94331;0.58218;,
 -10.95507;2.26738;-0.99189;,
 -11.10886;-0.78161;-0.82542;,
 -11.07631;0.66918;-1.43655;,
 -11.12530;-1.37125;0.62253;,
 -11.11603;-0.75430;2.05916;,
 -11.08649;0.70773;2.64289;,
 -11.05398;2.15848;2.03176;,
 -11.03753;2.74814;0.58381;,
 -11.04677;2.13123;-0.85282;,
 -11.08141;0.68845;0.60317;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  8;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.752800;0.602400;0.445600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.718431;0.718431;0.718431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.179200;0.179200;0.179200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.163200;0.401600;0.586400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.075200;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\Welcome2P.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\skirt001.png";
   }
  }
  Material {
   0.690400;0.636800;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  0.999770;-0.021280;0.002700;,
  0.978083;-0.022789;-0.206965;,
  0.974999;-0.169037;-0.144236;,
  0.973531;-0.228508;0.004595;,
  0.974260;-0.166226;0.152268;,
  0.977037;-0.018823;0.212238;,
  0.980513;0.127422;0.149523;,
  0.982382;0.186881;0.000693;,
  0.981258;0.124602;-0.146993;,
  0.765404;-0.022359;-0.643161;,
  0.756678;-0.473662;-0.450648;,
  0.752922;-0.658060;0.008105;,
  0.754387;-0.465025;0.463306;,
  0.762168;-0.010155;0.647300;,
  0.773685;0.441107;0.454791;,
  0.780252;0.625453;-0.003957;,
  0.775981;0.432453;-0.459171;,
  0.423287;-0.017533;-0.905826;,
  0.410696;-0.653288;-0.636037;,
  0.405076;-0.914232;0.009656;,
  0.407465;-0.641127;0.650329;,
  0.418734;-0.000386;0.908109;,
  0.434680;0.635295;0.638321;,
  0.443666;0.896162;-0.007365;,
  0.437895;0.623137;-0.648035;,
  0.187835;-0.013233;-0.982111;,
  0.173260;-0.702600;-0.690169;,
  0.166226;-0.986040;0.009736;,
  0.169783;-0.689417;0.704186;,
  0.182944;0.005346;0.983109;,
  0.199290;0.694665;0.691176;,
  0.208108;0.978067;-0.008727;,
  0.202762;0.681487;-0.703181;,
  0.046041;-0.010370;-0.998886;,
  0.030538;-0.711373;-0.702151;,
  0.022699;-0.999697;0.009507;,
  0.026996;-0.697968;0.715620;,
  0.041059;0.008518;0.999120;,
  0.056993;0.709507;0.702390;,
  0.065247;0.997826;-0.009275;,
  0.060514;0.696104;-0.715386;,
  -0.041049;-0.008517;-0.999121;,
  -0.056980;-0.709513;-0.702385;,
  -0.065258;-0.997825;0.009271;,
  -0.060531;-0.696106;0.715382;,
  -0.046037;0.010374;0.998886;,
  -0.030528;0.711376;0.702148;,
  -0.022683;0.999697;-0.009513;,
  -0.026985;0.697969;-0.715620;,
  -0.182957;-0.005344;-0.983106;,
  -0.199307;-0.694671;-0.691165;,
  -0.208107;-0.978067;0.008729;,
  -0.202762;-0.681491;0.703176;,
  -0.187835;0.013238;0.982111;,
  -0.173262;0.702606;0.690163;,
  -0.166228;0.986039;-0.009741;,
  -0.169782;0.689419;-0.704184;,
  -0.418717;0.000380;-0.908116;,
  -0.434632;-0.635317;-0.638331;,
  -0.443601;-0.896194;0.007361;,
  -0.437846;-0.623156;0.648049;,
  -0.423262;0.017535;0.905837;,
  -0.410694;0.653294;0.636033;,
  -0.405090;0.914226;-0.009659;,
  -0.407477;0.641124;-0.650325;,
  -0.762180;0.010159;-0.647285;,
  -0.773689;-0.441108;-0.454784;,
  -0.780276;-0.625423;0.003948;,
  -0.776034;-0.432410;0.459121;,
  -0.765454;0.022367;0.643102;,
  -0.756709;0.473646;0.450611;,
  -0.752936;0.658044;-0.008110;,
  -0.754404;0.465017;-0.463286;,
  -0.977047;0.018836;-0.212190;,
  -0.980528;-0.127377;-0.149466;,
  -0.982397;-0.186805;-0.000693;,
  -0.981278;-0.124534;0.146917;,
  -0.978101;0.022794;0.206880;,
  -0.975010;0.169006;0.144195;,
  -0.973534;0.228494;-0.004599;,
  -0.974264;0.166224;-0.152251;,
  -0.999770;0.021278;-0.002695;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;;
 }
 MeshTextureCoords {
  82;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}