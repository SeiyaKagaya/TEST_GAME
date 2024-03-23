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
 65;
 -0.07246;15.51276;-4.00419;,
 2.77725;14.43289;-6.85390;,
 -0.07246;14.43289;-8.03430;,
 -0.07246;15.51276;-4.00419;,
 3.95764;14.43289;-4.00419;,
 -0.07246;15.51276;-4.00419;,
 2.77725;14.43289;-1.15447;,
 -0.07246;15.51276;-4.00419;,
 -0.07246;14.43289;0.02592;,
 -0.07246;15.51276;-4.00419;,
 -2.92218;14.43289;-1.15447;,
 -0.07246;15.51276;-4.00419;,
 -4.10257;14.43289;-4.00419;,
 -0.07246;15.51276;-4.00419;,
 -2.92218;14.43289;-6.85390;,
 -0.07246;15.51276;-4.00419;,
 -0.07246;14.43289;-8.03430;,
 4.86339;11.48264;-8.94003;,
 -0.07246;11.48264;-10.22212;,
 6.90789;11.48264;-4.00419;,
 4.86339;11.48264;-0.09064;,
 -0.07246;11.48264;1.95386;,
 -5.00831;11.48264;-0.09064;,
 -7.05281;11.48264;-4.00419;,
 -5.00831;11.48264;-8.94003;,
 -0.07246;11.48264;-10.22212;,
 5.09784;7.45254;-9.70362;,
 -0.07246;7.45254;-10.41218;,
 11.24839;-11.57984;-0.06340;,
 6.76648;-16.96437;13.10022;,
 1.06704;-16.96437;15.46101;,
 -4.63239;-16.96437;13.10022;,
 -10.38681;-11.97921;0.05825;,
 -5.77189;7.45254;-9.70362;,
 -0.07246;7.45254;-10.41218;,
 4.86339;3.42243;-8.94003;,
 -0.07246;3.42243;-10.22212;,
 5.87412;3.42243;-4.00419;,
 4.86339;3.42243;-0.09064;,
 -0.07246;3.42243;1.95386;,
 -5.00831;3.42243;-0.09064;,
 -7.05281;3.42243;-4.00419;,
 -5.00831;3.42243;-8.94003;,
 -0.07246;3.42243;-10.22212;,
 2.77725;0.47218;-6.85390;,
 -0.07246;0.47218;-8.03430;,
 3.95764;0.47218;-4.00419;,
 2.77725;0.47218;-1.15447;,
 -0.07246;0.47218;0.02592;,
 -2.92218;0.47218;-1.15447;,
 -4.10257;0.47218;-4.00419;,
 -2.92218;0.47218;-6.85390;,
 -0.07246;0.47218;-8.03430;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -0.07246;-0.60768;-4.00419;,
 -6.67031;15.91347;-10.78670;,
 6.81291;15.82991;-10.41180;,
 6.74539;-0.71685;-10.44173;,
 -6.73784;-0.63336;-10.81662;;
 
 49;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 3;45,44,53;,
 3;44,46,54;,
 3;46,47,55;,
 3;47,48,56;,
 3;48,49,57;,
 3;49,50,58;,
 3;50,51,59;,
 3;51,52,60;,
 4;61,62,63,64;;
 
 MeshMaterialList {
  14;
  49;
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
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2;;
   Material {
   0.097600;0.097600;0.097600;1.000000;;
   30.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\black_hair.jpg";
   }
  }
  Material {
   0.708800;0.693600;0.580000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   1.000000;
   0.000000;0.000000;0.000000;;
   0.190000;0.190000;0.190000;;
   TextureFilename {
    "data\\TEXTURE\\57583335.png";
   }
  }
  Material {
   0.442400;0.279200;0.184800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\texture_00130.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
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
    "data\\TEXTURE\\r00607.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.125600;0.483200;0.132000;1.000000;;
   5.000000;
   0.530000;0.530000;0.530000;;
   0.078500;0.302000;0.082500;;
   TextureFilename {
    "data\\TEXTURE\\metal02.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184800;0.184800;0.184800;1.000000;;
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
    "data\\TEXTURE\\57583335_455x636.png";
   }
  }
  Material {
   0.558400;0.295200;0.147200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.432800;0.024800;0.075200;1.000000;;
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
    "data\\TEXTURE\\kuti.png";
   }
  }
 }
 MeshNormals {
  52;
  0.000000;1.000000;-0.000000;,
  0.000000;0.841893;-0.539644;,
  0.347302;0.860075;-0.373701;,
  0.503185;0.864104;0.011337;,
  0.375934;0.835396;0.400982;,
  0.000000;0.815540;0.578700;,
  -0.375934;0.835396;0.400982;,
  -0.503186;0.864104;0.011337;,
  -0.347302;0.860075;-0.373702;,
  0.001633;0.391768;-0.920062;,
  0.586004;0.437474;-0.682068;,
  0.882870;0.468905;0.025846;,
  0.599547;0.485128;0.636548;,
  -0.001053;0.489330;0.872098;,
  -0.600045;0.468721;0.648264;,
  -0.881743;0.469274;0.048074;,
  -0.588512;0.453891;-0.669056;,
  0.003142;0.000000;-0.999995;,
  0.489443;0.044139;-0.870917;,
  0.980067;0.196767;0.027414;,
  0.650231;0.349126;0.674767;,
  -0.002110;0.428853;0.903372;,
  -0.647593;0.314161;0.694209;,
  -0.977385;0.199239;0.070868;,
  -0.496692;0.062758;-0.865655;,
  0.001633;-0.391768;-0.920062;,
  0.020517;-0.475647;-0.879397;,
  -0.664730;-0.505236;-0.550337;,
  -0.639050;-0.485592;-0.596503;,
  0.003288;-0.552188;-0.833713;,
  0.616081;-0.425346;-0.662967;,
  0.707655;-0.436546;-0.555565;,
  0.039257;-0.482060;-0.875258;,
  0.000000;-0.841894;-0.539643;,
  0.379909;-0.848023;-0.369494;,
  0.557016;-0.830493;0.003815;,
  0.402928;-0.828936;0.387961;,
  0.000000;-0.815541;0.578699;,
  -0.375934;-0.835397;0.400982;,
  -0.503184;-0.864105;0.011337;,
  -0.347301;-0.860075;-0.373701;,
  0.000000;-1.000000;-0.000000;,
  -0.390094;-0.586174;-0.710089;,
  0.546164;-0.556519;-0.626092;,
  0.776813;-0.581156;-0.242527;,
  0.800978;-0.598649;0.007306;,
  0.588130;-0.584419;0.559069;,
  0.000000;-0.547036;0.837109;,
  -0.536418;-0.608414;0.584883;,
  -0.720453;-0.693144;0.022317;,
  -0.678599;-0.678597;-0.281086;,
  0.027804;0.001694;-0.999612;;
  49;
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
  4;42,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,43,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;44,45,35,34;,
  4;45,46,36,35;,
  4;46,47,37,36;,
  4;47,48,38,37;,
  4;48,49,39,38;,
  4;49,50,40,39;,
  4;32,25,33,40;,
  3;33,34,41;,
  3;34,35,41;,
  3;35,36,41;,
  3;36,37,41;,
  3;37,38,41;,
  3;38,39,41;,
  3;39,40,41;,
  3;40,33,41;,
  4;51,51,51,51;;
 }
 MeshTextureCoords {
  65;
  0.062500;0.000000;,
  0.125000;0.166670;,
  0.000000;0.166670;,
  0.187500;0.000000;,
  0.250000;0.166670;,
  0.312500;0.000000;,
  0.375000;0.166670;,
  0.437500;0.000000;,
  0.500000;0.166670;,
  0.562500;0.000000;,
  0.625000;0.166670;,
  0.687500;0.000000;,
  0.750000;0.166670;,
  0.812500;0.000000;,
  0.875000;0.166670;,
  0.937500;0.000000;,
  1.000000;0.166670;,
  0.125000;0.333330;,
  0.000000;0.333330;,
  0.250000;0.333330;,
  0.375000;0.333330;,
  0.500000;0.333330;,
  0.625000;0.333330;,
  0.750000;0.333330;,
  0.875000;0.333330;,
  1.000000;0.333330;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.666670;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.375000;0.666670;,
  0.500000;0.666670;,
  0.625000;0.666670;,
  0.750000;0.666670;,
  0.875000;0.666670;,
  1.000000;0.666670;,
  0.125000;0.833330;,
  0.000000;0.833330;,
  0.250000;0.833330;,
  0.375000;0.833330;,
  0.500000;0.833330;,
  0.625000;0.833330;,
  0.750000;0.833330;,
  0.875000;0.833330;,
  1.000000;0.833330;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
