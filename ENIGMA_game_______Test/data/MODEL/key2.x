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
 167;
 6.46820;14.08575;-1.11686;,
 9.04016;14.08575;-1.11686;,
 7.76740;9.33576;-1.11686;,
 5.54001;10.55194;-1.11686;,
 9.04016;14.08575;1.11686;,
 6.46820;14.08575;1.11686;,
 5.54001;10.55194;1.11686;,
 7.76740;9.33576;1.11686;,
 3.00418;7.96500;-1.11686;,
 4.29016;5.85852;-1.11686;,
 -0.45984;4.58576;-1.11686;,
 -0.45984;7.01812;-1.11686;,
 4.29016;5.85852;1.11686;,
 3.00418;7.96500;1.11686;,
 -0.45984;7.01812;1.11686;,
 -0.45984;4.58576;1.11686;,
 -5.20984;5.85852;-1.11686;,
 -3.92386;7.96500;-1.11686;,
 -3.92386;7.96500;1.11686;,
 -5.20984;5.85852;1.11686;,
 -6.45969;10.55194;-1.11686;,
 -8.68708;9.33576;-1.11686;,
 -9.95984;14.08575;-1.11686;,
 -7.38788;14.08575;-1.11686;,
 -8.68708;9.33576;1.11686;,
 -6.45969;10.55194;1.11686;,
 -7.38788;14.08575;1.11686;,
 -9.95984;14.08575;1.11686;,
 -8.68708;18.83576;-1.11686;,
 -6.45969;17.61957;-1.11686;,
 -6.45969;17.61957;1.11686;,
 -8.68708;18.83576;1.11686;,
 -5.20984;22.31299;-1.11686;,
 -3.92386;20.20651;-1.11686;,
 -3.92386;20.20651;1.11686;,
 -5.20984;22.31299;1.11686;,
 -0.45984;23.58575;-1.11686;,
 -0.45984;21.15340;-1.11686;,
 -0.45984;21.15340;1.11686;,
 -0.45984;23.58575;1.11686;,
 3.00418;20.20651;-1.11686;,
 4.29016;22.31300;-1.11686;,
 7.76740;18.83576;-1.11686;,
 5.54001;17.61958;-1.11700;,
 4.29016;22.31300;1.11686;,
 3.00418;20.20651;1.11686;,
 5.54001;17.61958;1.11700;,
 7.76740;18.83576;1.11686;,
 -2.14036;-0.43165;-2.00691;,
 -0.21609;-1.00164;0.00000;,
 -0.21144;-2.55278;0.00000;,
 -1.99160;-3.47946;-2.00691;,
 -2.14036;-0.43165;2.00691;,
 -1.99160;-3.47946;2.00691;,
 -4.06462;0.13835;-0.00000;,
 -3.77176;-4.40614;-0.00000;,
 1.02240;-6.85708;-2.00691;,
 1.87054;-5.03820;0.00000;,
 6.80707;-7.17908;0.00000;,
 5.18344;-8.35872;-2.00691;,
 1.02240;-6.85708;2.00691;,
 5.18344;-8.35872;2.00691;,
 -0.15053;-8.36237;-0.00000;,
 3.55983;-9.53835;-0.00000;,
 6.07699;-14.12077;0.00000;,
 4.69553;-12.66503;-2.00691;,
 4.69553;-12.66503;2.00691;,
 3.31409;-11.20926;-0.00000;,
 -12.75267;20.14487;0.00000;,
 -11.71903;21.86512;0.00000;,
 -12.75267;20.14487;-2.00691;,
 -12.75267;20.14487;2.00691;,
 -13.78630;18.42460;-0.00000;,
 0.58152;-25.42378;-0.00000;,
 0.58152;-19.64604;-2.00691;,
 2.45511;-20.36525;0.00000;,
 0.58152;-19.64604;2.00691;,
 -1.29210;-18.92681;-0.00000;,
 0.55609;-14.11215;-0.00000;,
 2.42969;-14.83138;-2.00691;,
 2.42969;-14.83138;2.00691;,
 4.30329;-15.55059;0.00000;,
 -0.94924;15.21978;0.00000;,
 2.96727;9.95835;0.00000;,
 0.97990;9.67904;-2.00691;,
 -1.98288;13.49953;-2.00691;,
 -1.98288;13.49953;2.00691;,
 0.97990;9.67904;2.00691;,
 -1.00748;9.39972;-0.00000;,
 -3.01650;11.77926;-0.00000;,
 -0.89268;2.78134;0.00000;,
 0.78755;2.09650;2.06040;,
 0.91913;2.06079;-1.97706;,
 1.51680;0.69135;0.00000;,
 3.39882;3.08455;-0.04250;,
 7.40743;-1.20621;0.62489;,
 7.80043;0.02332;-0.15812;,
 7.16588;-1.19176;-0.85526;,
 6.66516;-1.70681;-0.16986;,
 7.99857;-4.73025;-0.11558;,
 -1.11304;-5.73566;2.00691;,
 0.44286;-4.21202;0.00000;,
 -1.11304;-5.73566;-2.00691;,
 -0.56317;14.84416;1.51086;,
 2.14808;14.93334;-0.01457;,
 -0.52558;14.88737;-1.17239;,
 0.02793;16.82761;0.26721;,
 -0.56273;14.05131;1.45053;,
 2.19366;13.70678;-0.10100;,
 -0.64243;13.81871;-1.42533;,
 -0.65730;17.06801;0.15616;,
 -1.18094;15.57046;1.52134;,
 -1.08580;15.55937;-1.10641;,
 -1.81540;13.51559;2.00691;,
 -1.81540;13.51559;2.00691;,
 -1.81540;13.51559;-2.00691;,
 -1.81540;13.51559;-2.00691;,
 -1.81540;13.51559;2.00691;,
 0.90924;12.32704;-0.00000;,
 -0.56273;14.05131;1.45053;,
 -1.81540;13.51559;-2.00691;,
 -0.64243;13.81871;-1.42533;,
 0.90924;12.32704;-0.00000;,
 0.90924;12.32704;-0.00000;,
 2.19366;13.70678;-0.10100;,
 0.90924;12.32704;-0.00000;,
 -2.91406;16.08832;-0.00000;,
 -1.08580;15.55937;-1.10641;,
 -1.81540;13.51559;-2.00691;,
 -2.91406;16.08832;-0.00000;,
 -0.65730;17.06801;0.15616;,
 -1.81540;13.51559;2.00691;,
 -1.18094;15.57046;1.52134;,
 -2.91406;16.08832;-0.00000;,
 -2.91406;16.08832;-0.00000;,
 -2.43309;-6.99689;1.51086;,
 -5.14529;-6.94405;-0.01457;,
 -2.47289;-7.03807;-1.17239;,
 -3.12718;-8.94668;0.26721;,
 -2.39205;-6.20510;1.45053;,
 -5.12660;-5.71678;-0.10100;,
 -2.30027;-5.97699;-1.42533;,
 -2.45548;-9.22263;0.15616;,
 -1.85418;-7.75452;1.52134;,
 -1.94861;-7.73846;-1.10641;,
 -1.11304;-5.73566;2.00691;,
 -1.11304;-5.73566;2.00691;,
 -1.11304;-5.73566;-2.00691;,
 -1.11304;-5.73566;-2.00691;,
 -1.11304;-5.73566;2.00691;,
 -3.77176;-4.40614;-0.00000;,
 -2.39205;-6.20510;1.45053;,
 -1.11304;-5.73566;-2.00691;,
 -2.30027;-5.97699;-1.42533;,
 -3.77176;-4.40614;-0.00000;,
 -3.77176;-4.40614;-0.00000;,
 -5.12660;-5.71678;-0.10100;,
 -3.77176;-4.40614;-0.00000;,
 -0.15053;-8.36237;-0.00000;,
 -1.94861;-7.73846;-1.10641;,
 -1.11304;-5.73566;-2.00691;,
 -0.15053;-8.36237;-0.00000;,
 -2.45548;-9.22263;0.15616;,
 -1.11304;-5.73566;2.00691;,
 -1.85418;-7.75452;1.52134;,
 -0.15053;-8.36237;-0.00000;,
 -0.15053;-8.36237;-0.00000;;
 
 140;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;11,10,16,17;,
 4;15,14,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;23,22,28,29;,
 4;27,26,30,31;,
 4;29,28,32,33;,
 4;31,30,34,35;,
 4;33,32,36,37;,
 4;35,34,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;43,42,1,0;,
 4;47,46,5,4;,
 4;23,26,25,20;,
 4;29,30,26,23;,
 4;33,34,30,29;,
 4;33,37,38,34;,
 4;43,46,45,40;,
 4;3,6,5,0;,
 4;11,14,13,8;,
 4;17,18,14,11;,
 4;21,24,27,22;,
 4;10,15,19,16;,
 4;9,12,15,10;,
 4;1,4,7,2;,
 4;42,47,4,1;,
 4;41,44,47,42;,
 4;32,35,39,36;,
 4;28,31,35,32;,
 4;22,27,31,28;,
 4;44,41,40,45;,
 4;39,38,37,36;,
 4;20,25,24,21;,
 4;18,17,16,19;,
 4;3,8,13,6;,
 4;2,9,8,3;,
 4;2,7,12,9;,
 4;7,6,13,12;,
 4;46,43,0,5;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;54,48,51,55;,
 4;56,57,58,59;,
 4;57,60,61,58;,
 4;60,62,63,61;,
 4;62,56,59,63;,
 4;59,58,64,65;,
 4;58,61,66,64;,
 4;61,63,67,66;,
 4;63,59,65,67;,
 3;68,69,70;,
 3;68,71,69;,
 3;68,72,71;,
 3;68,70,72;,
 3;73,74,75;,
 3;73,75,76;,
 3;73,76,77;,
 3;73,77,74;,
 4;78,67,65,79;,
 4;78,79,74,77;,
 4;78,77,76,80;,
 4;78,80,66,67;,
 4;79,65,64,81;,
 4;79,81,75,74;,
 4;80,76,75,81;,
 4;80,81,64,66;,
 4;82,83,84,85;,
 4;82,85,70,69;,
 4;82,69,71,86;,
 4;82,86,87,83;,
 4;85,84,88,89;,
 4;85,89,72,70;,
 4;86,71,72,89;,
 4;86,89,88,87;,
 4;88,90,91,87;,
 4;90,54,52,91;,
 4;88,84,92,90;,
 4;92,48,54,90;,
 4;92,93,49,48;,
 4;92,84,83,94;,
 4;94,83,87,91;,
 4;52,49,93,91;,
 4;91,95,96,94;,
 4;94,96,97,92;,
 4;92,97,98,93;,
 4;91,93,98,95;,
 3;96,99,97;,
 3;96,95,99;,
 3;99,95,98;,
 3;99,98,97;,
 4;100,60,57,101;,
 4;100,101,50,53;,
 4;101,57,56,102;,
 4;101,102,51,50;,
 3;62,60,100;,
 3;102,56,62;,
 3;100,53,55;,
 3;55,51,102;,
 3;103,104,105;,
 3;105,106,103;,
 4;103,107,108,104;,
 4;109,105,104,108;,
 4;106,110,111,103;,
 4;105,112,110,106;,
 3;113,107,103;,
 3;103,111,114;,
 3;105,109,115;,
 3;116,112,105;,
 3;117,118,119;,
 3;120,121,122;,
 3;123,124,119;,
 3;121,124,125;,
 3;126,127,128;,
 3;129,130,127;,
 3;131,132,133;,
 3;134,132,130;,
 3;135,136,137;,
 3;137,138,135;,
 4;135,139,140,136;,
 4;141,137,136,140;,
 4;138,142,143,135;,
 4;137,144,142,138;,
 3;145,139,135;,
 3;135,143,146;,
 3;137,141,147;,
 3;148,144,137;,
 3;149,150,151;,
 3;152,153,154;,
 3;155,156,151;,
 3;153,156,157;,
 3;158,159,160;,
 3;161,162,159;,
 3;163,164,165;,
 3;166,164,162;;
 
 MeshMaterialList {
  6;
  140;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.432941;0.426667;0.087843;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.696471;0.696471;0.696471;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.501961;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.536471;0.003137;0.075294;1.000000;;
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
    "data\\TEXTURE\\blood.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\ki.jpg";
   }
  }
 }
 MeshNormals {
  180;
  0.000018;-0.000005;-1.000000;,
  0.000018;-0.000005;1.000000;,
  0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000001;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000001;-1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000001;-1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000001;1.000000;,
  0.000010;0.000037;-1.000000;,
  0.000011;0.000037;1.000000;,
  0.000023;0.000013;-1.000000;,
  0.000023;0.000013;1.000000;,
  1.000000;0.000000;0.000000;,
  0.967193;0.254041;0.000000;,
  0.869731;-0.493526;0.000000;,
  0.506484;-0.862249;0.000001;,
  0.263677;-0.964611;0.000001;,
  -0.869731;-0.493527;0.000000;,
  -0.714124;-0.700019;0.000000;,
  -0.869731;0.493527;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000000;1.000000;-0.000001;,
  -0.506484;0.862250;-0.000000;,
  0.263675;0.964611;-0.000001;,
  -0.965926;-0.258820;-0.000000;,
  -1.000000;-0.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.258819;-0.965926;-0.000000;,
  0.500000;-0.866025;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.866025;-0.500000;-0.000000;,
  0.866025;0.500000;0.000000;,
  0.707106;0.707107;0.000000;,
  -0.500000;0.866025;0.000000;,
  -0.258819;0.965926;0.000000;,
  -0.866025;0.500000;0.000000;,
  -0.853520;0.521061;0.000000;,
  1.000000;0.000000;0.000000;,
  0.479229;-0.877690;-0.000001;,
  -0.853519;0.521062;0.000000;,
  -0.857167;0.515038;0.000000;,
  -0.857165;0.515042;0.000000;,
  -0.857170;0.515034;0.000000;,
  0.666544;-0.301387;-0.681824;,
  0.664798;-0.296915;0.685482;,
  -0.656838;0.291045;0.695597;,
  0.700768;0.139908;-0.699535;,
  0.700768;0.139908;0.699535;,
  -0.700694;-0.150379;0.697434;,
  0.305614;0.648876;-0.696821;,
  0.305614;0.648876;0.696821;,
  -0.292095;-0.683689;0.668768;,
  0.601799;0.336133;-0.724467;,
  0.601799;0.336133;0.724467;,
  -0.593381;-0.353948;0.722925;,
  0.662984;-0.328675;-0.672625;,
  0.662984;-0.328675;0.672625;,
  -0.671081;0.315624;0.670845;,
  0.661633;-0.249507;-0.707098;,
  0.661633;-0.249507;0.707098;,
  -0.727434;0.018964;0.685915;,
  0.663111;-0.245605;-0.707080;,
  -0.591986;0.385305;-0.707879;,
  -0.591986;0.385305;0.707879;,
  0.578100;-0.404798;-0.708476;,
  0.646377;0.237702;0.725048;,
  -0.669649;-0.242416;-0.702001;,
  0.642707;0.240418;-0.727411;,
  0.485383;0.530042;-0.695312;,
  0.485383;0.530042;0.695312;,
  -0.477396;-0.537979;-0.694746;,
  -0.657056;0.313797;0.685426;,
  -0.345364;0.401874;-0.848069;,
  0.109528;-0.736172;-0.667873;,
  0.512558;0.240988;-0.824141;,
  0.663145;0.274228;0.696446;,
  0.544960;0.244376;-0.802059;,
  -0.511327;-0.536744;-0.671157;,
  0.718387;0.023723;-0.695239;,
  0.514378;0.449657;0.730222;,
  0.514378;0.449657;-0.730222;,
  -0.646089;0.292208;-0.705113;,
  -0.700694;-0.150379;-0.697434;,
  -0.292095;-0.683689;-0.668768;,
  -0.593381;-0.353948;-0.722925;,
  -0.671081;0.315624;-0.670845;,
  0.663111;-0.245605;0.707080;,
  -0.751126;-0.216612;0.623610;,
  -0.751126;-0.216612;-0.623610;,
  -0.727434;0.018964;-0.685915;,
  0.578100;-0.404798;0.708476;,
  0.371326;0.601791;-0.707082;,
  0.371326;0.601791;0.707082;,
  -0.371326;-0.601790;-0.707083;,
  -0.477396;-0.537979;0.694746;,
  -0.371326;-0.601790;0.707083;,
  -0.680183;-0.237519;0.693495;,
  -0.637456;0.309717;-0.705496;,
  0.630194;-0.300429;-0.715959;,
  0.540859;0.252511;0.802315;,
  0.587419;-0.036049;0.808480;,
  0.123998;-0.740299;0.660744;,
  -0.334122;-0.733498;-0.591897;,
  -0.305141;-0.756968;0.577831;,
  -0.485103;-0.533739;0.692674;,
  0.866024;0.040558;0.498355;,
  -0.618783;-0.259588;0.741432;,
  -0.649468;-0.298984;-0.699143;,
  -0.516928;-0.467033;0.717403;,
  -0.516928;-0.467033;-0.717403;,
  0.188430;0.675329;0.713039;,
  -0.024010;0.999587;0.015762;,
  0.959828;-0.280446;0.008928;,
  0.462556;-0.186926;0.866661;,
  0.463762;-0.198544;0.863426;,
  0.431620;-0.104430;-0.895990;,
  -0.112585;0.479052;0.870537;,
  -0.031415;0.648138;0.760874;,
  0.015859;0.520286;-0.853845;,
  0.429218;-0.068291;0.900615;,
  0.208545;0.163464;0.964255;,
  0.402438;0.168947;-0.899723;,
  0.262869;0.308892;-0.914049;,
  0.487157;-0.280007;0.827209;,
  0.484004;-0.286566;-0.826813;,
  0.429157;-0.338198;0.837524;,
  0.372971;-0.408195;-0.833228;,
  -0.348714;0.479337;-0.805378;,
  -0.238325;0.662219;-0.710399;,
  -0.556759;0.349927;0.753373;,
  -0.345459;0.695318;0.630230;,
  0.459100;-0.061504;0.886253;,
  0.488457;-0.054647;0.870875;,
  0.369904;0.279595;-0.886001;,
  0.409266;0.122078;-0.904211;,
  0.405983;-0.148496;-0.901736;,
  0.286333;0.524532;0.801798;,
  0.076793;0.615193;-0.784628;,
  0.383693;0.502327;-0.774885;,
  -0.223516;-0.664542;0.713039;,
  -0.028336;-0.999474;0.015759;,
  -0.943835;0.330295;0.008932;,
  -0.452140;0.210874;0.866661;,
  -0.452739;0.222539;0.863426;,
  -0.425564;0.126874;-0.895990;,
  0.087359;-0.484286;0.870538;,
  -0.002549;-0.648892;0.760876;,
  -0.043067;-0.518741;-0.853846;,
  -0.425052;0.090653;0.900618;,
  -0.216814;-0.152324;0.964256;,
  -0.410727;-0.147653;-0.899723;,
  -0.278672;-0.294711;-0.914050;,
  -0.471835;0.305119;0.827209;,
  -0.468345;0.311499;-0.826814;,
  -0.410872;0.360191;0.837524;,
  -0.351099;0.427151;-0.833229;,
  0.323147;-0.496930;-0.805380;,
  0.203341;-0.673779;-0.710404;,
  0.537681;-0.378584;0.753375;,
  0.308598;-0.712442;0.630233;,
  -0.455252;0.085441;0.886254;,
  -0.484929;0.080131;0.870875;,
  -0.384029;-0.259852;-0.886001;,
  -0.415096;-0.100490;-0.904211;,
  -0.397657;0.169538;-0.901735;,
  -0.313395;-0.508825;0.801798;,
  -0.108884;-0.610327;-0.784631;,
  -0.409457;-0.481557;-0.774886;;
  140;
  4;0,0,2,2;,
  4;1,1,3,3;,
  4;4,4,6,6;,
  4;5,5,7,7;,
  4;6,6,8,8;,
  4;7,7,9,9;,
  4;10,10,12,12;,
  4;11,11,13,13;,
  4;12,12,14,14;,
  4;13,13,15,15;,
  4;14,14,16,16;,
  4;15,15,17,17;,
  4;16,16,18,18;,
  4;17,17,19,19;,
  4;20,20,22,22;,
  4;21,21,23,23;,
  4;22,22,0,0;,
  4;23,23,1,1;,
  4;24,24,25,25;,
  4;26,26,24,24;,
  4;27,27,26,26;,
  4;27,28,28,27;,
  4;29,29,30,30;,
  4;31,31,32,32;,
  4;33,33,34,34;,
  4;35,35,33,33;,
  4;36,36,37,37;,
  4;38,38,39,39;,
  4;40,40,38,38;,
  4;41,41,42,42;,
  4;43,43,41,41;,
  4;44,44,43,43;,
  4;45,45,46,46;,
  4;47,47,45,45;,
  4;37,37,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;31,34,34,31;,
  4;2,4,4,2;,
  4;42,42,40,40;,
  4;3,3,5,5;,
  4;29,29,32,32;,
  4;55,55,58,58;,
  4;56,56,59,59;,
  4;57,57,60,60;,
  4;93,93,94,94;,
  4;61,61,64,64;,
  4;62,62,65,65;,
  4;63,63,66,66;,
  4;95,95,96,96;,
  4;64,64,67,67;,
  4;65,65,68,68;,
  4;66,66,69,69;,
  4;96,96,97,97;,
  3;52,53,52;,
  3;52,52,53;,
  3;52,54,52;,
  3;52,52,54;,
  3;73,70,70;,
  3;98,71,71;,
  3;99,72,72;,
  3;100,101,101;,
  4;74,97,97,74;,
  4;74,74,101,101;,
  4;75,72,72,75;,
  4;75,75,69,69;,
  4;76,67,67,76;,
  4;76,76,70,70;,
  4;102,71,71,102;,
  4;102,102,68,68;,
  4;80,79,79,80;,
  4;80,80,103,103;,
  4;81,104,104,81;,
  4;81,81,77,77;,
  4;82,78,78,82;,
  4;82,82,105,105;,
  4;106,107,107,106;,
  4;106,106,108,108;,
  4;108,83,83,108;,
  4;83,57,57,83;,
  4;78,78,84,109;,
  4;84,93,93,109;,
  4;110,85,55,55;,
  4;110,79,79,86;,
  4;111,77,77,112;,
  4;56,56,113,112;,
  4;112,87,87,111;,
  4;86,88,88,84;,
  4;114,89,89,85;,
  4;115,113,116,116;,
  3;88,90,88;,
  3;87,87,117;,
  3;118,116,116;,
  3;119,89,89;,
  4;91,62,62,91;,
  4;91,91,59,59;,
  4;92,61,61,92;,
  4;92,92,58,58;,
  3;63,63,120;,
  3;121,95,95;,
  3;120,60,60;,
  3;94,94,121;,
  3;122,123,123;,
  3;124,124,124;,
  4;143,125,126,144;,
  4;127,145,146,147;,
  4;148,129,128,122;,
  4;145,130,149,150;,
  3;131,125,143;,
  3;122,128,132;,
  3;145,127,133;,
  3;134,130,145;,
  3;135,135,125;,
  3;136,127,136;,
  3;137,126,125;,
  3;127,147,138;,
  3;139,130,139;,
  3;140,149,130;,
  3;141,128,141;,
  3;142,128,129;,
  3;151,152,152;,
  3;153,153,153;,
  4;172,154,155,173;,
  4;156,174,175,176;,
  4;177,158,157,151;,
  4;174,159,178,179;,
  3;160,154,172;,
  3;151,157,161;,
  3;174,156,162;,
  3;163,159,174;,
  3;164,164,154;,
  3;165,156,165;,
  3;166,155,154;,
  3;156,176,167;,
  3;168,159,168;,
  3;169,178,159;,
  3;170,157,170;,
  3;171,157,158;;
 }
 MeshTextureCoords {
  167;
  0.762448;0.195141;,
  0.762390;0.066587;,
  0.768556;0.123985;,
  0.766563;0.236908;,
  0.737610;0.066587;,
  0.737552;0.195141;,
  0.733437;0.236908;,
  0.731444;0.123985;,
  0.771966;0.360270;,
  0.779440;0.293235;,
  0.788131;0.528987;,
  0.775168;0.532172;,
  0.720560;0.293235;,
  0.728034;0.360270;,
  0.724832;0.532172;,
  0.711869;0.528987;,
  0.780689;0.768072;,
  0.772466;0.706553;,
  0.727534;0.706553;,
  0.719311;0.768072;,
  0.767060;0.836688;,
  0.769425;0.946427;,
  0.762834;1.016261;,
  0.762772;0.887707;,
  0.730575;0.946427;,
  0.732940;0.836688;,
  0.737228;0.887707;,
  0.737166;1.016261;,
  0.759544;0.958863;,
  0.760176;0.845940;,
  0.739824;0.845940;,
  0.740456;0.958863;,
  0.758011;0.789613;,
  0.758836;0.722579;,
  0.741164;0.722579;,
  0.741989;0.789613;,
  0.757537;0.553861;,
  0.758403;0.550677;,
  0.741597;0.550677;,
  0.742463;0.553861;,
  0.758757;0.376295;,
  0.757923;0.314776;,
  0.759329;0.136422;,
  0.759998;0.246161;,
  0.742077;0.314776;,
  0.741243;0.376295;,
  0.740003;0.246161;,
  0.740671;0.136422;,
  0.392982;0.521582;,
  0.489195;0.550082;,
  0.489428;0.627639;,
  0.400420;0.673973;,
  0.392982;0.521582;,
  0.400420;0.673973;,
  0.296769;0.493083;,
  0.311412;0.720307;,
  0.551120;0.842854;,
  0.593527;0.751910;,
  0.840353;0.858954;,
  0.759172;0.917936;,
  0.551120;0.842854;,
  0.759172;0.917936;,
  0.492473;0.918118;,
  0.677991;0.976917;,
  0.803850;1.206039;,
  0.734776;1.133251;,
  0.734776;1.133251;,
  0.665704;1.060463;,
  -0.137634;-0.507243;,
  -0.085952;-0.593256;,
  -0.137634;-0.507243;,
  -0.137634;-0.507243;,
  -0.189315;-0.421230;,
  0.529076;1.771189;,
  0.529076;1.482302;,
  0.622756;1.518263;,
  0.529076;1.482302;,
  0.435395;1.446340;,
  0.527804;1.205608;,
  0.621484;1.241569;,
  0.621484;1.241569;,
  0.715164;1.277529;,
  0.452538;-0.260989;,
  0.648363;0.002083;,
  0.548995;0.016048;,
  0.400856;-0.174976;,
  0.400856;-0.174976;,
  0.548995;0.016048;,
  0.449626;0.030014;,
  0.349175;-0.088963;,
  0.455366;0.360933;,
  0.539377;0.395175;,
  0.545956;0.396960;,
  0.575840;0.465432;,
  0.669941;0.345772;,
  0.870371;0.560311;,
  0.890021;0.498834;,
  0.858294;0.559588;,
  0.833258;0.585340;,
  0.899929;0.736512;,
  0.444348;0.786783;,
  0.522143;0.710601;,
  0.444348;0.786783;,
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
  0.409230;-0.175779;,
  0.545462;-0.116352;,
  0.471864;-0.202565;,
  0.409230;-0.175779;,
  0.467878;-0.190936;,
  0.545462;-0.116352;,
  0.545462;-0.116352;,
  0.609683;-0.185339;,
  0.545462;-0.116352;,
  0.354297;-0.304416;,
  0.445710;-0.277969;,
  0.409230;-0.175779;,
  0.354297;-0.304416;,
  0.467135;-0.353401;,
  0.409230;-0.175779;,
  0.440953;-0.278523;,
  0.354297;-0.304416;,
  0.354297;-0.304416;,
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
  0.444348;0.786783;,
  0.311412;0.720307;,
  0.380398;0.810255;,
  0.444348;0.786783;,
  0.384987;0.798849;,
  0.311412;0.720307;,
  0.311412;0.720307;,
  0.243670;0.785839;,
  0.311412;0.720307;,
  0.492473;0.918118;,
  0.402569;0.886923;,
  0.444348;0.786783;,
  0.492473;0.918118;,
  0.377226;0.961131;,
  0.444348;0.786783;,
  0.407291;0.887726;,
  0.492473;0.918118;,
  0.492473;0.918118;;
 }
}