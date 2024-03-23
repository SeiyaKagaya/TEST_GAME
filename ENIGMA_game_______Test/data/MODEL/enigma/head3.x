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
 34;
 15.99619;16.33963;-15.08546;,
 15.99619;16.33963;17.35881;,
 15.99619;-16.10463;17.35881;,
 15.99619;-16.10463;-15.08546;,
 15.99619;16.33963;17.35881;,
 -16.44803;16.33963;17.35881;,
 -16.44803;-16.10463;17.35881;,
 15.99619;-16.10463;17.35881;,
 -16.44803;16.33963;17.35881;,
 -16.44803;16.33963;-15.08546;,
 -16.44803;-16.10463;-15.08546;,
 -16.44803;-16.10463;17.35881;,
 15.99619;16.33963;-15.08546;,
 -16.44803;16.33963;-15.08546;,
 -16.44803;-16.10463;-15.08546;,
 15.99619;-16.10463;-15.08546;,
 -0.22592;7.41729;-15.08546;,
 -8.33696;4.98386;-15.08546;,
 7.88517;4.98386;-15.08546;,
 13.64668;0.11748;-15.08546;,
 -13.28517;0.11748;-15.08546;,
 -0.22592;-7.18261;-15.08546;,
 -8.33696;-4.74933;-15.08546;,
 7.88517;-4.74933;-15.08546;,
 -0.22592;0.11748;-17.12031;,
 6.79199;0.11748;-13.87724;,
 4.73653;-4.84514;-13.87724;,
 -0.22592;0.11748;-17.12031;,
 4.73653;5.07975;-13.87724;,
 -0.22592;0.11748;-17.12031;,
 -7.24389;0.11748;-13.87724;,
 -5.18833;5.07975;-13.87724;,
 -0.22592;0.11748;-17.12031;,
 -5.18833;-4.84514;-13.87724;;
 
 37;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,1,12,13;,
 4;14,15,2,11;,
 3;12,16,13;,
 3;16,17,13;,
 3;16,12,18;,
 3;19,18,12;,
 3;13,17,20;,
 3;10,21,3;,
 3;10,22,21;,
 3;21,23,3;,
 3;13,20,10;,
 3;19,12,3;,
 3;3,23,19;,
 3;20,22,10;,
 3;24,25,26;,
 3;27,28,25;,
 3;29,30,31;,
 3;32,33,30;,
 3;31,16,27;,
 3;16,28,27;,
 3;21,33,27;,
 3;27,26,21;,
 3;16,31,17;,
 3;18,28,16;,
 3;26,23,21;,
 3;21,22,33;,
 3;31,20,17;,
 3;31,30,20;,
 3;20,30,33;,
 3;33,22,20;,
 3;26,19,23;,
 3;25,19,26;,
 3;28,18,19;,
 3;19,25,28;;
 
 MeshMaterialList {
  4;
  37;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.420000;0.420000;0.420000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  27;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.104396;-0.994536;,
  0.159266;-0.312754;-0.936386;,
  -0.157761;-0.326831;-0.931822;,
  -0.151799;-0.000007;-0.988411;,
  0.159305;-0.000006;-0.987229;,
  -0.000000;-0.104393;-0.994536;,
  0.159260;0.312743;-0.936391;,
  -0.157755;0.326818;-0.931828;,
  0.000000;0.000006;-1.000000;,
  0.066150;0.013468;-0.997719;,
  0.126936;0.000002;-0.991911;,
  0.066151;-0.013475;-0.997719;,
  -0.058168;-0.002137;-0.998304;,
  -0.115597;0.000002;-0.993296;,
  -0.058167;0.002131;-0.998305;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000001;-0.818280;-0.574820;,
  0.238416;-0.794683;-0.558245;,
  -0.238415;-0.794684;-0.558244;,
  -0.238399;0.794680;-0.558256;,
  0.000001;0.818273;-0.574830;,
  0.238401;0.794679;-0.558257;;
  37;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  3;20,3,20;,
  3;3,4,20;,
  3;3,20,5;,
  3;6,5,20;,
  3;20,4,7;,
  3;20,8,20;,
  3;20,9,8;,
  3;8,10,20;,
  3;20,7,20;,
  3;6,20,20;,
  3;20,10,6;,
  3;7,9,20;,
  3;11,13,12;,
  3;11,14,13;,
  3;11,16,15;,
  3;11,17,16;,
  3;15,3,11;,
  3;3,14,11;,
  3;8,17,11;,
  3;11,12,8;,
  3;21,22,4;,
  3;5,23,21;,
  3;24,10,25;,
  3;25,9,26;,
  3;15,7,4;,
  3;15,16,7;,
  3;7,16,17;,
  3;17,9,7;,
  3;12,6,10;,
  3;13,6,12;,
  3;14,5,6;,
  3;6,13,14;;
 }
 MeshTextureCoords {
  34;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.125000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.625000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;;
 }
}
