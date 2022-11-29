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
 248;
 -6.58940;-46.98150;8.85030;,
 6.58940;-46.98150;8.85030;,
 6.58940;-5.78280;8.85030;,
 -6.58940;-5.78280;8.85030;,
 9.41310;-5.78280;-5.49330;,
 9.41310;-5.78280;5.78080;,
 9.41310;-46.98150;5.78080;,
 9.41310;-46.98150;-5.49330;,
 -9.41310;-46.98150;5.78080;,
 -9.41310;-46.98150;-5.49330;,
 -6.58940;-46.98150;8.85030;,
 -9.41310;-46.98150;-8.26880;,
 -8.70570;-46.98150;-8.97620;,
 8.70570;-46.98150;-8.97620;,
 6.58940;-46.98150;8.85030;,
 9.41310;-46.98150;5.78080;,
 9.41310;-46.98150;-5.49330;,
 9.41310;-46.98150;-8.26880;,
 -9.41310;-5.78280;5.78080;,
 -9.41310;-46.98150;5.78080;,
 -6.58940;-46.98150;8.85030;,
 -6.58940;-5.78280;8.85030;,
 6.58940;-5.78280;8.85030;,
 6.58940;-46.98150;8.85030;,
 -9.41310;-5.78280;-5.49330;,
 -9.41310;-46.98150;-5.49330;,
 -9.41310;-5.78280;-5.49330;,
 -9.41310;-5.78280;5.78080;,
 9.41310;-5.78280;-5.49330;,
 -6.58940;-5.78280;8.85030;,
 6.58940;-5.78280;8.85030;,
 9.41310;-5.78280;5.78080;,
 9.41310;-5.78280;-5.49330;,
 9.41310;5.17390;-10.85890;,
 -9.41310;5.17390;-10.85890;,
 -9.41310;-5.78280;-5.49330;,
 8.53720;0.10840;2.69180;,
 5.85900;0.10840;2.69180;,
 5.85900;-2.47760;3.76300;,
 8.53720;-2.47760;3.76300;,
 5.85900;-5.06360;2.69180;,
 8.53720;-5.06360;2.69180;,
 8.53720;-5.06360;2.69180;,
 5.85900;-5.06360;2.69180;,
 5.85900;-6.13470;0.10590;,
 8.53720;-6.13470;0.10590;,
 5.85900;-5.06360;-2.48010;,
 8.53720;-5.06360;-2.48010;,
 8.53720;-5.06360;-2.48010;,
 5.85900;-5.06360;-2.48010;,
 5.85900;-2.47760;-3.55130;,
 8.53720;-2.47760;-3.55130;,
 5.85900;0.10840;-2.48010;,
 8.53720;0.10840;-2.48010;,
 8.53720;0.10840;-2.48010;,
 5.85900;0.10840;-2.48010;,
 5.85900;1.17950;0.10590;,
 8.53720;1.17950;0.10590;,
 5.85900;0.10840;2.69180;,
 8.53720;0.10840;2.69180;,
 8.53720;-2.47760;3.76300;,
 8.53720;-2.47760;0.10590;,
 8.53720;0.10840;2.69180;,
 8.53720;-5.06360;2.69180;,
 8.53720;-6.13470;0.10590;,
 8.53720;-5.06360;-2.48010;,
 8.53720;-2.47760;-3.55130;,
 8.53720;0.10840;-2.48010;,
 8.53720;1.17950;0.10590;,
 5.85900;0.10840;2.69180;,
 5.85900;-2.47760;0.10590;,
 5.85900;-2.47760;3.76300;,
 5.85900;-5.06360;2.69180;,
 5.85900;-6.13470;0.10590;,
 5.85900;-5.06360;-2.48010;,
 5.85900;-2.47760;-3.55130;,
 5.85900;0.10840;-2.48010;,
 5.85900;1.17950;0.10590;,
 -5.60000;0.10840;2.69180;,
 -8.27820;0.10840;2.69180;,
 -8.27820;-2.47760;3.76300;,
 -5.60000;-2.47760;3.76300;,
 -8.27820;-5.06360;2.69180;,
 -5.60000;-5.06360;2.69180;,
 -5.60000;-5.06360;2.69180;,
 -8.27820;-5.06360;2.69180;,
 -8.27820;-6.13470;0.10590;,
 -5.60000;-6.13470;0.10590;,
 -8.27820;-5.06360;-2.48010;,
 -5.60000;-5.06360;-2.48010;,
 -5.60000;-5.06360;-2.48010;,
 -8.27820;-5.06360;-2.48010;,
 -8.27820;-2.47760;-3.55130;,
 -5.60000;-2.47760;-3.55130;,
 -8.27820;0.10840;-2.48010;,
 -5.60000;0.10840;-2.48010;,
 -5.60000;0.10840;-2.48010;,
 -8.27820;0.10840;-2.48010;,
 -8.27820;1.17950;0.10590;,
 -5.60000;1.17950;0.10590;,
 -8.27820;0.10840;2.69180;,
 -5.60000;0.10840;2.69180;,
 -5.60000;-2.47760;3.76300;,
 -5.60000;-2.47760;0.10590;,
 -5.60000;0.10840;2.69180;,
 -5.60000;-5.06360;2.69180;,
 -5.60000;-6.13470;0.10590;,
 -5.60000;-5.06360;-2.48010;,
 -5.60000;-2.47760;-3.55130;,
 -5.60000;0.10840;-2.48010;,
 -5.60000;1.17950;0.10590;,
 -8.27820;0.10840;2.69180;,
 -8.27820;-2.47760;0.10590;,
 -8.27820;-2.47760;3.76300;,
 -8.27820;-5.06360;2.69180;,
 -8.27820;-6.13470;0.10590;,
 -8.27820;-5.06360;-2.48010;,
 -8.27820;-2.47760;-3.55130;,
 -8.27820;0.10840;-2.48010;,
 -8.27820;1.17950;0.10590;,
 -9.41310;6.02840;-12.98460;,
 -9.41310;5.17390;-10.85890;,
 -8.70570;6.39450;-13.89540;,
 9.41310;5.17390;-10.85890;,
 8.70570;6.39450;-13.89540;,
 9.41310;6.02840;-12.98460;,
 -9.41310;-46.98150;-8.26880;,
 -9.41310;-5.64530;-8.26880;,
 -8.70570;-5.78280;-8.97620;,
 -8.70570;-46.98150;-8.97620;,
 -9.41310;6.02840;-12.98460;,
 -8.70570;6.39450;-13.89540;,
 8.70570;-46.98150;-8.97620;,
 8.70570;-5.78280;-8.97620;,
 9.41310;-5.64530;-8.26880;,
 9.41310;-46.98150;-8.26880;,
 8.70570;6.39450;-13.89540;,
 9.41310;6.02840;-12.98460;,
 -8.70570;-5.78280;-8.97620;,
 8.70570;-5.78280;-8.97620;,
 8.70570;-46.98150;-8.97620;,
 -8.70570;-46.98150;-8.97620;,
 -8.70570;6.39450;-13.89540;,
 8.70570;6.39450;-13.89540;,
 9.41310;5.17390;-10.85890;,
 -9.41310;5.17390;-10.85890;,
 2.07030;-5.83830;2.81700;,
 3.79510;-4.20840;4.54180;,
 0.03580;-4.20840;6.09900;,
 0.03580;-5.83830;3.65980;,
 -3.72350;-4.20840;4.54180;,
 -1.99870;-5.83830;2.81700;,
 -1.99870;-5.83830;2.81700;,
 -3.72350;-4.20840;4.54180;,
 -5.28070;-4.20840;0.78250;,
 -2.84150;-5.83830;0.78250;,
 -3.72350;-4.20840;-2.97680;,
 -1.99870;-5.83830;-1.25200;,
 -1.99870;-5.83830;-1.25200;,
 -3.72350;-4.20840;-2.97680;,
 0.03580;-4.20840;-4.53400;,
 0.03580;-5.83830;-2.09480;,
 3.79510;-4.20840;-2.97680;,
 2.07030;-5.83830;-1.25200;,
 2.07030;-5.83830;-1.25200;,
 3.79510;-4.20840;-2.97680;,
 5.35230;-4.20840;0.78250;,
 2.91310;-5.83830;0.78250;,
 3.79510;-4.20840;4.54180;,
 2.07030;-5.83830;2.81700;,
 4.94760;-1.76920;5.69430;,
 0.03580;-1.76920;7.72880;,
 -4.87600;-1.76920;5.69430;,
 -4.87600;-1.76920;5.69430;,
 -6.91050;-1.76920;0.78250;,
 -4.87600;-1.76920;-4.12930;,
 -4.87600;-1.76920;-4.12930;,
 0.03580;-1.76920;-6.16380;,
 4.94760;-1.76920;-4.12930;,
 4.94760;-1.76920;-4.12930;,
 6.98210;-1.76920;0.78250;,
 4.94760;-1.76920;5.69430;,
 4.94760;-1.76920;5.69430;,
 5.35230;1.10800;6.09900;,
 0.03580;1.10800;8.30110;,
 0.03580;-1.76920;7.72880;,
 -5.28070;1.10800;6.09900;,
 -4.87600;-1.76920;5.69430;,
 -5.28070;1.10800;6.09900;,
 -7.48280;1.10800;0.78250;,
 -5.28070;1.10800;-4.53400;,
 -4.87600;-1.76920;-4.12930;,
 -5.28070;1.10800;-4.53400;,
 0.03580;1.10800;-6.73610;,
 0.03580;-1.76920;-6.16380;,
 5.35230;1.10800;-4.53400;,
 4.94760;-1.76920;-4.12930;,
 5.35230;1.10800;-4.53400;,
 7.55440;1.10800;0.78250;,
 5.35230;1.10800;6.09900;,
 4.94760;3.98530;5.69430;,
 0.03580;3.98530;7.72880;,
 -4.87600;3.98530;5.69430;,
 -4.87600;3.98530;5.69430;,
 -6.91050;3.98530;0.78250;,
 -4.87600;3.98530;-4.12930;,
 -4.87600;3.98530;-4.12930;,
 0.03580;3.98530;-6.16380;,
 4.94760;3.98530;-4.12930;,
 4.94760;3.98530;-4.12930;,
 6.98210;3.98530;0.78250;,
 4.94760;3.98530;5.69430;,
 4.94760;3.98530;5.69430;,
 3.79510;6.42450;4.54180;,
 0.03580;6.42450;6.09900;,
 0.03580;3.98530;7.72880;,
 -3.72350;6.42450;4.54180;,
 -4.87600;3.98530;5.69430;,
 -3.72350;6.42450;4.54180;,
 -5.28070;6.42450;0.78250;,
 -3.72350;6.42450;-2.97680;,
 -4.87600;3.98530;-4.12930;,
 -3.72350;6.42450;-2.97680;,
 0.03580;6.42450;-4.53400;,
 0.03580;3.98530;-6.16380;,
 3.79510;6.42450;-2.97680;,
 4.94760;3.98530;-4.12930;,
 3.79510;6.42450;-2.97680;,
 5.35230;6.42450;0.78250;,
 3.79510;6.42450;4.54180;,
 2.07030;8.05440;2.81700;,
 0.03580;8.05440;3.65980;,
 -1.99870;8.05440;2.81700;,
 -1.99870;8.05440;2.81700;,
 -2.84150;8.05440;0.78250;,
 -1.99870;8.05440;-1.25200;,
 -1.99870;8.05440;-1.25200;,
 0.03580;8.05440;-2.09480;,
 2.07030;8.05440;-1.25200;,
 2.07030;8.05440;-1.25200;,
 2.91310;8.05440;0.78250;,
 2.07030;8.05440;2.81700;,
 0.03580;-6.41060;0.78250;,
 -2.84150;-5.83830;0.78250;,
 2.91310;-5.83830;0.78250;,
 0.03580;8.62670;0.78250;,
 -2.84150;8.05440;0.78250;,
 2.91310;8.05440;0.78250;;
 
 144;
 4;0,1,2,3;,
 4;4,5,6,7;,
 3;8,9,10;,
 3;11,12,9;,
 3;9,12,10;,
 3;12,13,10;,
 3;10,13,14;,
 3;14,13,15;,
 3;13,16,15;,
 3;16,13,17;,
 4;18,19,20,21;,
 4;22,23,6,5;,
 4;18,24,25,19;,
 3;26,27,28;,
 3;27,29,28;,
 3;29,30,28;,
 3;28,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;54,55,56,57;,
 4;57,56,58,59;,
 3;60,61,62;,
 3;63,61,60;,
 3;64,61,63;,
 3;65,61,64;,
 3;66,61,65;,
 3;67,61,66;,
 3;68,61,67;,
 3;62,61,68;,
 3;69,70,71;,
 3;71,70,72;,
 3;72,70,73;,
 3;73,70,74;,
 3;74,70,75;,
 3;75,70,76;,
 3;76,70,77;,
 3;77,70,69;,
 4;78,79,80,81;,
 4;81,80,82,83;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;90,91,92,93;,
 4;93,92,94,95;,
 4;96,97,98,99;,
 4;99,98,100,101;,
 3;102,103,104;,
 3;105,103,102;,
 3;106,103,105;,
 3;107,103,106;,
 3;108,103,107;,
 3;109,103,108;,
 3;110,103,109;,
 3;104,103,110;,
 3;111,112,113;,
 3;113,112,114;,
 3;114,112,115;,
 3;115,112,116;,
 3;116,112,117;,
 3;117,112,118;,
 3;118,112,119;,
 3;119,112,111;,
 3;120,121,122;,
 3;121,123,122;,
 3;122,123,124;,
 3;124,123,125;,
 4;126,127,128,129;,
 4;127,130,131,128;,
 4;132,133,134,135;,
 4;133,136,137,134;,
 4;138,139,140,141;,
 4;24,127,126,25;,
 4;134,4,7,135;,
 4;138,142,143,139;,
 4;134,137,144,4;,
 4;24,145,130,127;,
 4;146,147,148,149;,
 4;149,148,150,151;,
 4;152,153,154,155;,
 4;155,154,156,157;,
 4;158,159,160,161;,
 4;161,160,162,163;,
 4;164,165,166,167;,
 4;167,166,168,169;,
 4;147,170,171,148;,
 4;148,171,172,150;,
 4;153,173,174,154;,
 4;154,174,175,156;,
 4;159,176,177,160;,
 4;160,177,178,162;,
 4;165,179,180,166;,
 4;166,180,181,168;,
 4;182,183,184,185;,
 4;185,184,186,187;,
 4;173,188,189,174;,
 4;174,189,190,175;,
 4;191,192,193,194;,
 4;194,193,195,196;,
 4;179,197,198,180;,
 4;180,198,199,181;,
 4;183,200,201,184;,
 4;184,201,202,186;,
 4;188,203,204,189;,
 4;189,204,205,190;,
 4;192,206,207,193;,
 4;193,207,208,195;,
 4;197,209,210,198;,
 4;198,210,211,199;,
 4;212,213,214,215;,
 4;215,214,216,217;,
 4;203,218,219,204;,
 4;204,219,220,205;,
 4;221,222,223,224;,
 4;224,223,225,226;,
 4;209,227,228,210;,
 4;210,228,229,211;,
 4;213,230,231,214;,
 4;214,231,232,216;,
 4;218,233,234,219;,
 4;219,234,235,220;,
 4;222,236,237,223;,
 4;223,237,238,225;,
 4;227,239,240,228;,
 4;228,240,241,229;,
 3;149,242,146;,
 3;151,242,149;,
 3;243,242,151;,
 3;158,242,243;,
 3;161,242,158;,
 3;163,242,161;,
 3;244,242,163;,
 3;146,242,244;,
 3;230,245,231;,
 3;231,245,232;,
 3;232,245,246;,
 3;246,245,236;,
 3;236,245,237;,
 3;237,245,238;,
 3;238,245,247;,
 3;247,245,230;;
 
 MeshMaterialList {
  6;
  144;
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
  5;;
  Material {
   0.648000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex1.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\machingun.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex2.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex3.png";
   }
  }
 }
 MeshNormals {
  98;
  -0.931654;0.000000;0.363346;,
  -0.401855;0.000000;0.915703;,
  -0.000000;-1.000000;0.000000;,
  0.401855;0.000000;0.915703;,
  0.931654;0.000000;0.363346;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.000010;0.847711;0.530458;,
  0.000013;0.812995;0.582271;,
  0.000000;0.707114;0.707100;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.707114;0.707100;,
  0.000000;-1.000000;0.000007;,
  0.000000;-0.707118;-0.707095;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.707118;-0.707095;,
  0.000000;1.000000;0.000007;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000007;,
  0.000000;-0.707118;-0.707095;,
  0.000000;-0.000000;-1.000000;,
  0.000000;1.000000;0.000007;,
  -0.926351;-0.071861;-0.369743;,
  -0.388768;-0.175776;-0.904413;,
  0.388768;-0.175776;-0.904413;,
  0.926351;-0.071861;-0.369743;,
  0.000037;0.927840;0.372978;,
  0.000012;0.927842;0.372973;,
  -0.000037;0.927840;0.372978;,
  -0.000019;0.927842;0.372974;,
  0.269139;-0.924732;0.269138;,
  0.000000;-0.924735;0.380611;,
  -0.269139;-0.924732;0.269138;,
  -0.380613;-0.924734;0.000000;,
  -0.269139;-0.924731;-0.269139;,
  -0.000000;-0.924734;-0.380613;,
  0.269139;-0.924731;-0.269139;,
  0.380613;-0.924734;-0.000000;,
  0.498499;-0.709223;0.498499;,
  0.000000;-0.709228;0.704979;,
  -0.498499;-0.709224;0.498498;,
  -0.704982;-0.709226;0.000000;,
  -0.498499;-0.709223;-0.498499;,
  0.000000;-0.709226;-0.704981;,
  0.498500;-0.709222;-0.498500;,
  0.704982;-0.709226;-0.000000;,
  0.652732;-0.384554;0.652732;,
  0.000000;-0.384554;0.923103;,
  -0.652732;-0.384555;0.652732;,
  -0.923103;-0.384553;0.000000;,
  -0.652732;-0.384555;-0.652732;,
  0.000000;-0.384554;-0.923102;,
  0.652732;-0.384554;-0.652732;,
  0.923103;-0.384553;-0.000000;,
  0.707107;-0.000003;0.707107;,
  0.000000;-0.000003;1.000000;,
  -0.707107;-0.000003;0.707107;,
  -1.000000;-0.000003;0.000000;,
  -0.707107;-0.000003;-0.707107;,
  0.000000;-0.000003;-1.000000;,
  0.707107;-0.000003;-0.707107;,
  1.000000;-0.000003;-0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.384550;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384551;-0.652733;,
  0.000000;0.384550;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384550;0.000000;,
  0.498499;0.709223;0.498499;,
  0.000000;0.709227;0.704980;,
  -0.498499;0.709223;0.498499;,
  -0.704982;0.709226;0.000000;,
  -0.498500;0.709222;-0.498500;,
  -0.000000;0.709225;-0.704982;,
  0.498500;0.709222;-0.498500;,
  0.704982;0.709226;0.000000;,
  0.269139;0.924732;0.269138;,
  0.000000;0.924735;0.380611;,
  -0.269139;0.924732;0.269138;,
  -0.380613;0.924734;0.000000;,
  -0.269139;0.924731;-0.269139;,
  -0.000000;0.924734;-0.380613;,
  0.269139;0.924731;-0.269139;,
  0.380613;0.924734;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.439805;0.898093;,
  -0.923880;0.000000;-0.382683;,
  -0.382683;0.000000;-0.923880;,
  -0.923878;-0.143339;-0.354829;,
  -0.382680;-0.346047;-0.856626;,
  0.382683;0.000000;-0.923880;,
  0.923880;0.000000;-0.382683;,
  0.382680;-0.346047;-0.856626;,
  0.923878;-0.143339;-0.354829;;
  144;
  4;1,3,3,1;,
  4;7,4,4,7;,
  3;2,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;0,0,1,1;,
  4;3,3,4,4;,
  4;0,5,5,0;,
  3;88,88,88;,
  3;88,88,88;,
  3;88,88,88;,
  3;88,88,87;,
  4;89,8,9,89;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,10,10;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;10,10,18,18;,
  4;18,18,12,12;,
  4;12,12,19,19;,
  4;19,19,20,20;,
  4;20,20,21,21;,
  4;21,21,16,16;,
  4;16,16,22,22;,
  4;22,22,10,10;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;27,9,28;,
  3;9,8,28;,
  3;28,8,30;,
  3;30,8,29;,
  4;90,23,24,91;,
  4;23,92,93,24;,
  4;94,25,26,95;,
  4;25,96,97,26;,
  4;24,25,94,91;,
  4;5,23,90,5;,
  4;26,7,7,95;,
  4;24,93,96,25;,
  4;26,97,7,7;,
  4;5,5,92,23;,
  4;31,39,40,32;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,39,31;,
  4;39,47,48,40;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,47,39;,
  4;47,55,56,48;,
  4;48,56,57,49;,
  4;49,57,58,50;,
  4;50,58,59,51;,
  4;51,59,60,52;,
  4;52,60,61,53;,
  4;53,61,62,54;,
  4;54,62,55,47;,
  4;55,63,64,56;,
  4;56,64,65,57;,
  4;57,65,66,58;,
  4;58,66,67,59;,
  4;59,67,68,60;,
  4;60,68,69,61;,
  4;61,69,70,62;,
  4;62,70,63,55;,
  4;63,71,72,64;,
  4;64,72,73,65;,
  4;65,73,74,66;,
  4;66,74,75,67;,
  4;67,75,76,68;,
  4;68,76,77,69;,
  4;69,77,78,70;,
  4;70,78,71,63;,
  4;71,79,80,72;,
  4;72,80,81,73;,
  4;73,81,82,74;,
  4;74,82,83,75;,
  4;75,83,84,76;,
  4;76,84,85,77;,
  4;77,85,86,78;,
  4;78,86,79,71;,
  3;32,2,31;,
  3;33,2,32;,
  3;34,2,33;,
  3;35,2,34;,
  3;36,2,35;,
  3;37,2,36;,
  3;38,2,37;,
  3;31,2,38;,
  3;79,87,80;,
  3;80,87,81;,
  3;81,87,82;,
  3;82,87,83;,
  3;83,87,84;,
  3;84,87,85;,
  3;85,87,86;,
  3;86,87,79;;
 }
 MeshTextureCoords {
  248;
  0.827850;0.471430;,
  0.872100;0.471430;,
  0.872100;0.609760;,
  0.827850;0.609760;,
  0.914970;0.769540;,
  0.952270;0.769540;,
  0.952270;0.905820;,
  0.914970;0.905820;,
  0.823030;0.971250;,
  0.823070;0.936790;,
  0.831650;0.980640;,
  0.823080;0.928310;,
  0.825240;0.926150;,
  0.878460;0.926200;,
  0.871940;0.980690;,
  0.880580;0.971320;,
  0.880620;0.936850;,
  0.880630;0.928370;,
  0.744930;0.769070;,
  0.744930;0.908180;,
  0.734570;0.908180;,
  0.734570;0.769070;,
  0.962420;0.769540;,
  0.962420;0.905820;,
  0.782990;0.769070;,
  0.782990;0.908180;,
  0.815900;0.671490;,
  0.815780;0.630350;,
  0.884600;0.671300;,
  0.826060;0.619120;,
  0.874150;0.618980;,
  0.884490;0.630160;,
  0.884610;0.673230;,
  0.884720;0.713220;,
  0.816020;0.713410;,
  0.815900;0.673420;,
  0.925750;0.568300;,
  0.897990;0.568300;,
  0.897990;0.541500;,
  0.925750;0.541500;,
  0.897990;0.514710;,
  0.925750;0.514710;,
  0.925330;0.568300;,
  0.897580;0.568300;,
  0.897580;0.541500;,
  0.925330;0.541500;,
  0.897580;0.514710;,
  0.925330;0.514710;,
  0.925870;0.568300;,
  0.898120;0.568300;,
  0.898120;0.541500;,
  0.925870;0.541500;,
  0.898120;0.514710;,
  0.925870;0.514710;,
  0.924980;0.568300;,
  0.897230;0.568300;,
  0.897230;0.541500;,
  0.924980;0.541500;,
  0.897230;0.514710;,
  0.924980;0.514710;,
  0.979560;0.622150;,
  0.941660;0.622150;,
  0.968460;0.595350;,
  0.968460;0.648950;,
  0.941660;0.660050;,
  0.914860;0.648950;,
  0.903760;0.622150;,
  0.914860;0.595350;,
  0.941660;0.584250;,
  0.950700;0.547140;,
  0.960250;0.556680;,
  0.946750;0.556680;,
  0.950700;0.566220;,
  0.960250;0.570180;,
  0.969790;0.566220;,
  0.973740;0.556680;,
  0.969790;0.547140;,
  0.960250;0.543190;,
  0.925050;0.568420;,
  0.897290;0.568420;,
  0.897290;0.541620;,
  0.925050;0.541620;,
  0.897290;0.514820;,
  0.925050;0.514820;,
  0.925580;0.568420;,
  0.897830;0.568420;,
  0.897830;0.541620;,
  0.925580;0.541620;,
  0.897830;0.514820;,
  0.925580;0.514820;,
  0.925650;0.568420;,
  0.897890;0.568420;,
  0.897890;0.541620;,
  0.925650;0.541620;,
  0.897890;0.514820;,
  0.925650;0.514820;,
  0.925890;0.566490;,
  0.899050;0.566490;,
  0.899050;0.540580;,
  0.925890;0.540580;,
  0.899050;0.514660;,
  0.925890;0.514660;,
  0.973760;0.556330;,
  0.960270;0.556330;,
  0.969810;0.546790;,
  0.969810;0.565870;,
  0.960270;0.569830;,
  0.950730;0.565870;,
  0.946770;0.556330;,
  0.950730;0.546790;,
  0.960270;0.542840;,
  0.725480;0.593550;,
  0.752280;0.620350;,
  0.714380;0.620350;,
  0.725480;0.647150;,
  0.752280;0.658250;,
  0.779080;0.647150;,
  0.790180;0.620350;,
  0.779080;0.593550;,
  0.752280;0.582450;,
  0.816040;0.723100;,
  0.816020;0.715340;,
  0.818630;0.726410;,
  0.884730;0.715140;,
  0.882180;0.726240;,
  0.884750;0.722900;,
  0.792370;0.908180;,
  0.792370;0.768610;,
  0.794750;0.769070;,
  0.794750;0.908180;,
  0.808290;0.729190;,
  0.811370;0.727960;,
  0.903450;0.905820;,
  0.903450;0.769540;,
  0.905790;0.769080;,
  0.905790;0.905820;,
  0.887180;0.729260;,
  0.890190;0.730470;,
  0.822320;0.774980;,
  0.878070;0.774980;,
  0.878070;0.906890;,
  0.822320;0.906890;,
  0.822320;0.735990;,
  0.878070;0.735990;,
  0.897220;0.733290;,
  0.801110;0.732080;,
  0.970230;0.508750;,
  0.975270;0.513790;,
  0.964290;0.518330;,
  0.964290;0.511210;,
  0.953320;0.513790;,
  0.958350;0.508750;,
  0.959310;0.523090;,
  0.954270;0.518330;,
  0.965250;0.518330;,
  0.965250;0.523090;,
  0.976230;0.518330;,
  0.971190;0.523090;,
  0.958350;0.496870;,
  0.953320;0.491830;,
  0.964290;0.487290;,
  0.964290;0.494410;,
  0.975270;0.491830;,
  0.970230;0.496870;,
  0.959090;0.524120;,
  0.954050;0.519360;,
  0.965030;0.519360;,
  0.965030;0.524120;,
  0.976000;0.519360;,
  0.970970;0.524120;,
  0.978630;0.517150;,
  0.964290;0.523090;,
  0.949950;0.517150;,
  0.950910;0.511210;,
  0.965250;0.511210;,
  0.979590;0.511210;,
  0.949950;0.488470;,
  0.964290;0.482530;,
  0.978630;0.488470;,
  0.950690;0.512240;,
  0.965030;0.512240;,
  0.979370;0.512240;,
  0.973870;0.516820;,
  0.965470;0.518000;,
  0.965470;0.502480;,
  0.973870;0.502480;,
  0.965470;0.486950;,
  0.973870;0.488140;,
  0.949730;0.502810;,
  0.965250;0.502810;,
  0.980770;0.502810;,
  0.957200;0.487620;,
  0.965600;0.486440;,
  0.965600;0.501960;,
  0.957200;0.501960;,
  0.965600;0.517490;,
  0.957200;0.516300;,
  0.949510;0.503840;,
  0.965030;0.503840;,
  0.980550;0.503840;,
  0.957070;0.516820;,
  0.957070;0.502480;,
  0.957070;0.488140;,
  0.950910;0.494410;,
  0.965250;0.494410;,
  0.979590;0.494410;,
  0.974000;0.487620;,
  0.974000;0.501960;,
  0.974000;0.516300;,
  0.950690;0.495440;,
  0.965030;0.495440;,
  0.979370;0.495440;,
  0.979970;0.489540;,
  0.976610;0.492910;,
  0.965630;0.488360;,
  0.965630;0.483600;,
  0.954660;0.492910;,
  0.951290;0.489540;,
  0.954270;0.487290;,
  0.965250;0.487290;,
  0.976230;0.487290;,
  0.951290;0.518230;,
  0.954660;0.514860;,
  0.965630;0.519410;,
  0.965630;0.524170;,
  0.976610;0.514860;,
  0.979970;0.518230;,
  0.954050;0.488310;,
  0.965030;0.488310;,
  0.976000;0.488310;,
  0.971570;0.497940;,
  0.965630;0.495480;,
  0.959690;0.497940;,
  0.959310;0.482530;,
  0.965250;0.482530;,
  0.971190;0.482530;,
  0.959690;0.509820;,
  0.965630;0.512280;,
  0.971570;0.509820;,
  0.959090;0.483560;,
  0.965030;0.483560;,
  0.970970;0.483560;,
  0.964290;0.502810;,
  0.955890;0.502810;,
  0.972690;0.502810;,
  0.965630;0.503880;,
  0.957230;0.503880;,
  0.974040;0.503880;;
 }
}