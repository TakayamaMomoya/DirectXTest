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
 278;
 -6.05990;-30.39960;-5.23400;,
 -6.05990;-30.39960;5.23400;,
 -8.30270;-28.15680;5.23400;,
 -8.30270;-28.15680;-5.23400;,
 -6.05990;-28.15680;-7.47680;,
 4.99450;-28.15680;-7.47680;,
 4.99450;-30.39960;-5.23400;,
 -6.05990;-30.39960;-5.23400;,
 -8.30270;-3.21830;-5.23400;,
 -6.05990;-3.21830;-7.47680;,
 -6.05990;-28.15680;-7.47680;,
 7.23730;-28.15680;-5.23400;,
 7.23730;-28.15680;5.23400;,
 4.99450;-30.39960;5.23400;,
 4.99450;-30.39960;-5.23400;,
 4.99450;-28.15680;-7.47680;,
 4.99450;-3.21830;-7.47680;,
 8.30270;-5.34100;-5.23400;,
 -8.30270;-3.21830;5.23400;,
 -6.05990;-0.97550;5.23400;,
 -6.05990;-0.97550;-5.23400;,
 -6.05990;-0.97550;-5.23400;,
 4.99450;-0.97550;-5.23400;,
 4.99450;-3.21830;-7.47680;,
 -6.05990;-3.21830;-7.47680;,
 4.99450;-0.97550;-5.23400;,
 4.99450;-0.97550;5.23400;,
 8.30270;-5.34100;5.23400;,
 -6.05990;-28.15680;7.47680;,
 -6.05990;-3.21830;7.47680;,
 -6.05990;-3.21830;7.47680;,
 4.99450;-3.21830;7.47680;,
 4.99450;-0.97550;5.23400;,
 -6.05990;-0.97550;5.23400;,
 4.99450;-3.21830;7.47680;,
 4.99450;-28.15680;7.47680;,
 -6.05990;-30.39960;5.23400;,
 4.99450;-30.39960;5.23400;,
 4.99450;-28.15680;7.47680;,
 -6.05990;-28.15680;7.47680;,
 -6.05990;-28.15680;-7.47680;,
 -6.05990;-3.21830;-7.47680;,
 4.99450;-3.21830;-7.47680;,
 4.99450;-28.15680;-7.47680;,
 -6.05990;-3.21830;7.47680;,
 -6.05990;-28.15680;7.47680;,
 4.99450;-28.15680;7.47680;,
 4.99450;-3.21830;7.47680;,
 1.19340;-4.29870;1.70740;,
 2.47430;-3.08840;2.98820;,
 -0.31750;-3.08840;4.14460;,
 -0.31750;-4.29870;2.33320;,
 -3.10920;-3.08840;2.98820;,
 -1.82840;-4.29870;1.70740;,
 -1.82840;-4.29870;1.70740;,
 -3.10920;-3.08840;2.98820;,
 -4.26560;-3.08840;0.19650;,
 -2.45420;-4.29870;0.19650;,
 -3.10920;-3.08840;-2.59530;,
 -1.82840;-4.29870;-1.31440;,
 -1.82840;-4.29870;-1.31440;,
 -3.10920;-3.08840;-2.59530;,
 -0.31750;-3.08840;-3.75170;,
 -0.31750;-4.29870;-1.94030;,
 2.47430;-3.08840;-2.59530;,
 1.19340;-4.29870;-1.31440;,
 1.19340;-4.29870;-1.31440;,
 2.47430;-3.08840;-2.59530;,
 3.63070;-3.08840;0.19650;,
 1.81920;-4.29870;0.19650;,
 2.47430;-3.08840;2.98820;,
 1.19340;-4.29870;1.70740;,
 3.33010;-1.27700;3.84410;,
 -0.31750;-1.27700;5.35500;,
 -3.96510;-1.27700;3.84410;,
 -3.96510;-1.27700;3.84410;,
 -5.47600;-1.27700;0.19650;,
 -3.96510;-1.27700;-3.45120;,
 -3.96510;-1.27700;-3.45120;,
 -0.31750;-1.27700;-4.96200;,
 3.33010;-1.27700;-3.45120;,
 3.33010;-1.27700;-3.45120;,
 4.84100;-1.27700;0.19650;,
 3.33010;-1.27700;3.84410;,
 3.33010;-1.27700;3.84410;,
 3.63070;0.85980;4.14460;,
 -0.31750;0.85980;5.78000;,
 -0.31750;-1.27700;5.35500;,
 -4.26560;0.85980;4.14460;,
 -3.96510;-1.27700;3.84410;,
 -4.26560;0.85980;4.14460;,
 -5.90100;0.85980;0.19650;,
 -4.26560;0.85980;-3.75170;,
 -3.96510;-1.27700;-3.45120;,
 -4.26560;0.85980;-3.75170;,
 -0.31750;0.85980;-5.38710;,
 -0.31750;-1.27700;-4.96200;,
 3.63070;0.85980;-3.75170;,
 3.33010;-1.27700;-3.45120;,
 3.63070;0.85980;-3.75170;,
 5.26600;0.85980;0.19650;,
 3.63070;0.85980;4.14460;,
 3.33010;2.99650;3.84410;,
 -0.31750;2.99650;5.35500;,
 -3.96510;2.99650;3.84410;,
 -3.96510;2.99650;3.84410;,
 -5.47600;2.99650;0.19650;,
 -3.96510;2.99650;-3.45120;,
 -3.96510;2.99650;-3.45120;,
 -0.31750;2.99650;-4.96200;,
 3.33010;2.99650;-3.45120;,
 3.33010;2.99650;-3.45120;,
 4.84100;2.99650;0.19650;,
 3.33010;2.99650;3.84410;,
 3.33010;2.99650;3.84410;,
 2.47430;4.80790;2.98820;,
 -0.31750;4.80790;4.14460;,
 -0.31750;2.99650;5.35500;,
 -3.10920;4.80790;2.98820;,
 -3.96510;2.99650;3.84410;,
 -3.10920;4.80790;2.98820;,
 -4.26560;4.80790;0.19650;,
 -3.10920;4.80790;-2.59530;,
 -3.96510;2.99650;-3.45120;,
 -3.10920;4.80790;-2.59530;,
 -0.31750;4.80790;-3.75170;,
 -0.31750;2.99650;-4.96200;,
 2.47430;4.80790;-2.59530;,
 3.33010;2.99650;-3.45120;,
 2.47430;4.80790;-2.59530;,
 3.63070;4.80790;0.19650;,
 2.47430;4.80790;2.98820;,
 1.19340;6.01830;1.70740;,
 -0.31750;6.01830;2.33320;,
 -1.82840;6.01830;1.70740;,
 -1.82840;6.01830;1.70740;,
 -2.45420;6.01830;0.19650;,
 -1.82840;6.01830;-1.31440;,
 -1.82840;6.01830;-1.31440;,
 -0.31750;6.01830;-1.94030;,
 1.19340;6.01830;-1.31440;,
 1.19340;6.01830;-1.31440;,
 1.81920;6.01830;0.19650;,
 1.19340;6.01830;1.70740;,
 -0.31750;-4.72380;0.19650;,
 -2.45420;-4.29870;0.19650;,
 1.81920;-4.29870;0.19650;,
 -0.31750;6.44330;0.19650;,
 -2.45420;6.01830;0.19650;,
 1.81920;6.01830;0.19650;,
 -0.59190;-36.01090;-0.64250;,
 -4.79810;-41.70570;-0.64250;,
 -5.93400;-40.79410;-0.64250;,
 -1.72780;-35.09930;-0.64250;,
 -4.79810;-41.70570;-0.64250;,
 -4.79810;-41.70570;5.29950;,
 -5.93400;-40.79410;5.29950;,
 -5.93400;-40.79410;-0.64250;,
 -4.79810;-41.70570;5.29950;,
 -0.59190;-36.01090;5.29950;,
 -1.72780;-35.09930;5.29950;,
 -5.93400;-40.79410;5.29950;,
 -0.59190;-36.01090;5.29950;,
 -0.59190;-36.01090;-0.64250;,
 -1.72780;-35.09930;-0.64250;,
 -1.72780;-35.09930;5.29950;,
 -1.72780;-35.09930;-0.64250;,
 -1.72780;-35.09930;5.29950;,
 -0.59190;-36.01090;5.29950;,
 -0.59190;-36.01090;-0.64250;,
 -4.16170;-40.86620;-0.64250;,
 -0.69920;-44.08770;-0.64250;,
 -1.69130;-45.15400;-0.64250;,
 -5.15380;-41.93260;-0.64250;,
 -0.69920;-44.08770;-0.64250;,
 -0.69920;-44.08770;5.29950;,
 -1.69130;-45.15400;5.29950;,
 -1.69130;-45.15400;-0.64250;,
 -0.69920;-44.08770;5.29950;,
 -4.16170;-40.86620;5.29950;,
 -5.15380;-41.93260;5.29950;,
 -1.69130;-45.15400;5.29950;,
 -4.16170;-40.86620;5.29950;,
 -4.16170;-40.86620;-0.64250;,
 -5.15380;-41.93260;-0.64250;,
 -5.15380;-41.93260;5.29950;,
 -5.15380;-41.93260;-0.64250;,
 -5.15380;-41.93260;5.29950;,
 -4.16170;-40.86620;5.29950;,
 -4.16170;-40.86620;-0.64250;,
 -1.84020;-43.86370;-0.64250;,
 1.80000;-40.84440;-0.64250;,
 2.72990;-41.96550;-0.64250;,
 -0.91030;-44.98470;-0.64250;,
 1.80000;-40.84440;-0.64250;,
 1.80000;-40.84440;5.29950;,
 2.72990;-41.96550;5.29950;,
 2.72990;-41.96550;-0.64250;,
 1.80000;-40.84440;5.29950;,
 -1.84020;-43.86370;5.29950;,
 -0.91030;-44.98470;5.29950;,
 2.72990;-41.96550;5.29950;,
 -1.84020;-43.86370;5.29950;,
 -1.84020;-43.86370;-0.64250;,
 -0.91030;-44.98470;-0.64250;,
 -0.91030;-44.98470;5.29950;,
 -0.91030;-44.98470;-0.64250;,
 -0.91030;-44.98470;5.29950;,
 -1.84020;-43.86370;5.29950;,
 -1.84020;-43.86370;-0.64250;,
 0.36370;-42.46290;-4.70620;,
 0.36370;-30.41100;-4.70620;,
 3.89110;-30.41100;-4.70620;,
 3.89110;-42.46290;-4.70620;,
 0.36370;-30.41100;-4.70620;,
 0.36370;-30.41100;5.94690;,
 3.89110;-30.41100;5.94690;,
 3.89110;-30.41100;-4.70620;,
 0.36370;-30.41100;5.94690;,
 0.36370;-42.46290;5.94690;,
 3.89110;-42.46290;5.94690;,
 3.89110;-30.41100;5.94690;,
 0.36370;-42.46290;5.94690;,
 0.36370;-42.46290;-4.70620;,
 3.89110;-42.46290;-4.70620;,
 3.89110;-42.46290;5.94690;,
 3.89110;-42.46290;-4.70620;,
 3.89110;-30.41100;-4.70620;,
 3.89110;-30.41100;5.94690;,
 3.89110;-42.46290;5.94690;,
 0.36370;-42.46290;5.94690;,
 0.36370;-30.41100;5.94690;,
 0.36370;-30.41100;-4.70620;,
 0.36370;-42.46290;-4.70620;,
 -2.55340;-42.59900;-4.29530;,
 -6.00950;-35.77840;-4.44490;,
 -4.52470;-35.02620;-4.45590;,
 -1.06860;-41.84680;-4.30620;,
 -6.00950;-35.77840;-4.44490;,
 -6.01870;-35.71570;-1.37630;,
 -4.53380;-34.96360;-1.38720;,
 -4.52470;-35.02620;-4.45590;,
 -6.01870;-35.71570;-1.37630;,
 -2.56260;-42.53630;-1.22670;,
 -1.07780;-41.78420;-1.23760;,
 -4.53380;-34.96360;-1.38720;,
 -2.56260;-42.53630;-1.22670;,
 -2.55340;-42.59900;-4.29530;,
 -1.06860;-41.84680;-4.30620;,
 -1.07780;-41.78420;-1.23760;,
 -1.06860;-41.84680;-4.30620;,
 -4.52470;-35.02620;-4.45590;,
 -4.53380;-34.96360;-1.38720;,
 -1.07780;-41.78420;-1.23760;,
 -2.56260;-42.53630;-1.22670;,
 -6.01870;-35.71570;-1.37630;,
 -6.00950;-35.77840;-4.44490;,
 -2.55340;-42.59900;-4.29530;,
 -5.53310;-35.56720;-4.29530;,
 0.68730;-31.12060;-4.44490;,
 1.65510;-32.47480;-4.45590;,
 -4.56530;-36.92140;-4.30620;,
 0.68730;-31.12060;-4.44490;,
 0.74780;-31.10200;-1.37630;,
 1.71560;-32.45630;-1.38720;,
 1.65510;-32.47480;-4.45590;,
 0.74780;-31.10200;-1.37630;,
 -5.47250;-35.54870;-1.22670;,
 -4.50470;-36.90290;-1.23760;,
 1.71560;-32.45630;-1.38720;,
 -5.47250;-35.54870;-1.22670;,
 -5.53310;-35.56720;-4.29530;,
 -4.56530;-36.92140;-4.30620;,
 -4.50470;-36.90290;-1.23760;,
 -4.56530;-36.92140;-4.30620;,
 -4.50470;-36.90290;-1.23760;,
 0.74780;-31.10200;-1.37630;,
 0.68730;-31.12060;-4.44490;;
 
 126;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,8,9,10;,
 4;11,12,13,14;,
 4;15,16,17,11;,
 4;8,18,19,20;,
 4;21,22,23,24;,
 4;25,26,27,17;,
 4;18,2,28,29;,
 4;30,31,32,33;,
 4;34,35,12,27;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;21,33,32,22;,
 4;44,45,46,47;,
 4;36,7,6,37;,
 4;11,17,27,12;,
 4;2,18,8,3;,
 3;0,3,10;,
 3;11,14,15;,
 3;8,20,9;,
 3;25,17,16;,
 3;18,29,19;,
 3;34,27,26;,
 3;2,1,28;,
 3;13,12,35;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;54,55,56,57;,
 4;57,56,58,59;,
 4;60,61,62,63;,
 4;63,62,64,65;,
 4;66,67,68,69;,
 4;69,68,70,71;,
 4;49,72,73,50;,
 4;50,73,74,52;,
 4;55,75,76,56;,
 4;56,76,77,58;,
 4;61,78,79,62;,
 4;62,79,80,64;,
 4;67,81,82,68;,
 4;68,82,83,70;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;75,90,91,76;,
 4;76,91,92,77;,
 4;93,94,95,96;,
 4;96,95,97,98;,
 4;81,99,100,82;,
 4;82,100,101,83;,
 4;85,102,103,86;,
 4;86,103,104,88;,
 4;90,105,106,91;,
 4;91,106,107,92;,
 4;94,108,109,95;,
 4;95,109,110,97;,
 4;99,111,112,100;,
 4;100,112,113,101;,
 4;114,115,116,117;,
 4;117,116,118,119;,
 4;105,120,121,106;,
 4;106,121,122,107;,
 4;123,124,125,126;,
 4;126,125,127,128;,
 4;111,129,130,112;,
 4;112,130,131,113;,
 4;115,132,133,116;,
 4;116,133,134,118;,
 4;120,135,136,121;,
 4;121,136,137,122;,
 4;124,138,139,125;,
 4;125,139,140,127;,
 4;129,141,142,130;,
 4;130,142,143,131;,
 3;51,144,48;,
 3;53,144,51;,
 3;145,144,53;,
 3;60,144,145;,
 3;63,144,60;,
 3;65,144,63;,
 3;146,144,65;,
 3;48,144,146;,
 3;132,147,133;,
 3;133,147,134;,
 3;134,147,148;,
 3;148,147,138;,
 3;138,147,139;,
 3;139,147,140;,
 3;140,147,149;,
 3;149,147,132;,
 4;150,151,152,153;,
 4;154,155,156,157;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;166,157,156,167;,
 4;168,155,154,169;,
 4;170,171,172,173;,
 4;174,175,176,177;,
 4;178,179,180,181;,
 4;182,183,184,185;,
 4;186,177,176,187;,
 4;188,175,174,189;,
 4;190,191,192,193;,
 4;194,195,196,197;,
 4;198,199,200,201;,
 4;202,203,204,205;,
 4;206,197,196,207;,
 4;208,195,194,209;,
 4;210,211,212,213;,
 4;214,215,216,217;,
 4;218,219,220,221;,
 4;222,223,224,225;,
 4;226,227,228,229;,
 4;230,231,232,233;,
 4;234,235,236,237;,
 4;238,239,240,241;,
 4;242,243,244,245;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;254,255,256,257;,
 4;258,259,260,261;,
 4;262,263,264,265;,
 4;266,267,268,269;,
 4;270,271,272,273;,
 4;274,265,264,275;,
 4;270,276,277,271;;
 
 MeshMaterialList {
  6;
  126;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
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
   0.800000;0.800000;0.800000;1.000000;;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex3.png";
   }
  }
 }
 MeshNormals {
  123;
  -0.478625;-0.851254;-0.215137;,
  -0.215137;-0.478625;-0.851254;,
  -0.851254;-0.478626;-0.215137;,
  0.844019;-0.492025;-0.213410;,
  0.343415;-0.367965;-0.864099;,
  0.215137;-0.851254;-0.478625;,
  -0.851254;0.215137;-0.478626;,
  -0.478625;0.215137;-0.851254;,
  -0.478625;0.851254;-0.215137;,
  0.259522;0.846058;-0.465654;,
  0.378164;0.346175;-0.858577;,
  0.861634;0.168673;-0.478682;,
  -0.851254;0.478626;0.215137;,
  -0.478625;0.851254;0.215137;,
  -0.478625;0.215137;0.851254;,
  0.378164;0.346175;0.858577;,
  0.560946;0.804303;0.196052;,
  0.901134;0.390660;0.187996;,
  -0.851254;-0.478626;0.215137;,
  -0.478625;-0.215137;0.851254;,
  -0.478625;-0.851254;0.215137;,
  0.478625;-0.851254;0.215137;,
  0.343415;-0.367965;0.864099;,
  0.844019;-0.492025;0.213410;,
  0.269136;-0.924732;0.269140;,
  -0.000001;-0.924729;0.380626;,
  -0.269141;-0.924730;0.269141;,
  -0.380626;-0.924729;0.000001;,
  -0.269147;-0.924730;-0.269135;,
  -0.000002;-0.924734;-0.380613;,
  0.269139;-0.924734;-0.269130;,
  0.380615;-0.924733;0.000001;,
  0.498486;-0.709239;0.498490;,
  -0.000002;-0.709242;0.704966;,
  -0.498485;-0.709242;0.498485;,
  -0.704964;-0.709243;0.000003;,
  -0.498489;-0.709242;-0.498483;,
  -0.000003;-0.709241;-0.704966;,
  0.498488;-0.709241;-0.498485;,
  0.704969;-0.709238;0.000004;,
  0.652734;-0.384550;0.652732;,
  -0.000002;-0.384555;0.923102;,
  -0.652733;-0.384553;0.652732;,
  -0.923102;-0.384554;0.000005;,
  -0.652731;-0.384556;-0.652732;,
  -0.000002;-0.384555;-0.923102;,
  0.652733;-0.384552;-0.652732;,
  0.923106;-0.384545;0.000005;,
  0.707109;0.000005;0.707105;,
  -0.000003;0.000004;1.000000;,
  -0.707107;0.000004;0.707107;,
  -1.000000;0.000004;0.000005;,
  -0.707107;0.000005;-0.707107;,
  -0.000003;0.000005;-1.000000;,
  0.707108;0.000005;-0.707105;,
  1.000000;0.000005;0.000005;,
  0.652733;0.384554;0.652731;,
  -0.000002;0.384559;0.923101;,
  -0.652731;0.384557;0.652731;,
  -0.923101;0.384558;0.000005;,
  -0.652730;0.384560;-0.652731;,
  -0.000002;0.384560;-0.923100;,
  0.652731;0.384557;-0.652731;,
  0.923104;0.384550;0.000005;,
  0.498496;0.709225;0.498500;,
  -0.000002;0.709228;0.704979;,
  -0.498496;0.709227;0.498496;,
  -0.704980;0.709228;0.000004;,
  -0.498499;0.709228;-0.498493;,
  -0.000003;0.709228;-0.704980;,
  0.498498;0.709227;-0.498495;,
  0.704983;0.709224;0.000004;,
  0.269133;0.924734;0.269137;,
  -0.000001;0.924731;0.380621;,
  -0.269140;0.924731;0.269139;,
  -0.380623;0.924730;0.000001;,
  -0.269144;0.924732;-0.269132;,
  -0.000002;0.924736;-0.380609;,
  0.269136;0.924736;-0.269127;,
  0.380611;0.924735;0.000001;,
  0.000000;-1.000000;0.000002;,
  0.000000;1.000000;0.000002;,
  0.000000;0.000000;-1.000000;,
  -0.625899;-0.779904;0.000000;,
  0.000000;0.000000;1.000000;,
  0.732120;-0.681175;-0.000000;,
  0.769688;0.638420;0.000000;,
  0.000000;1.000000;0.000000;,
  0.002976;-0.020428;-0.999787;,
  -0.451910;0.891849;-0.019556;,
  -0.002998;0.020410;0.999787;,
  -0.019745;-0.006027;-0.999787;,
  0.813367;0.581422;-0.019551;,
  0.019722;0.006047;0.999787;,
  0.000000;-0.707107;-0.707107;,
  -0.707107;0.000000;-0.707107;,
  0.707107;-0.707107;-0.000000;,
  0.636882;-0.016577;-0.770783;,
  -0.707107;0.707107;0.000000;,
  0.000000;0.707107;-0.707107;,
  0.797004;0.603974;0.000000;,
  -0.707107;0.000000;0.707107;,
  0.000000;0.707107;0.707107;,
  0.636882;-0.016577;0.770783;,
  0.000000;-0.707107;0.707107;,
  0.625899;0.779904;0.000000;,
  -0.804379;0.594117;0.000000;,
  0.804379;-0.594117;-0.000000;,
  -0.732152;0.681141;0.000000;,
  -0.681157;-0.732137;0.000000;,
  0.681169;0.732127;0.000000;,
  -0.769660;-0.638454;0.000000;,
  0.638398;-0.769706;-0.000000;,
  -0.638411;0.769696;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.451921;-0.891843;0.019563;,
  0.892060;0.451870;-0.006558;,
  -0.892057;-0.451875;0.006559;,
  -0.813357;-0.581436;0.019568;,
  0.581424;-0.813575;-0.006568;,
  -0.581428;0.813571;0.006554;;
  126;
  4;0,20,18,2;,
  4;1,4,5,94;,
  4;95,6,7,95;,
  4;3,23,21,96;,
  4;4,10,11,97;,
  4;98,12,13,8;,
  4;99,9,10,99;,
  4;100,16,17,100;,
  4;101,101,19,14;,
  4;102,15,102,102;,
  4;15,22,103,103;,
  4;104,104,22,104;,
  4;1,7,10,4;,
  4;8,13,16,9;,
  4;14,19,22,15;,
  4;20,0,5,21;,
  4;3,11,17,23;,
  4;18,12,6,2;,
  3;0,2,1;,
  3;3,5,4;,
  3;6,8,7;,
  3;9,11,10;,
  3;12,14,13;,
  3;15,17,16;,
  3;18,20,19;,
  3;21,23,22;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,32,24;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,40,32;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,48,40;,
  4;48,56,57,49;,
  4;49,57,58,50;,
  4;50,58,59,51;,
  4;51,59,60,52;,
  4;52,60,61,53;,
  4;53,61,62,54;,
  4;54,62,63,55;,
  4;55,63,56,48;,
  4;56,64,65,57;,
  4;57,65,66,58;,
  4;58,66,67,59;,
  4;59,67,68,60;,
  4;60,68,69,61;,
  4;61,69,70,62;,
  4;62,70,71,63;,
  4;63,71,64,56;,
  4;64,72,73,65;,
  4;65,73,74,66;,
  4;66,74,75,67;,
  4;67,75,76,68;,
  4;68,76,77,69;,
  4;69,77,78,70;,
  4;70,78,79,71;,
  4;71,79,72,64;,
  3;25,80,24;,
  3;26,80,25;,
  3;27,80,26;,
  3;28,80,27;,
  3;29,80,28;,
  3;30,80,29;,
  3;31,80,30;,
  3;24,80,31;,
  3;72,81,73;,
  3;73,81,74;,
  3;74,81,75;,
  3;75,81,76;,
  3;76,81,77;,
  3;77,81,78;,
  3;78,81,79;,
  3;79,81,72;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;107,107,107,107;,
  4;82,82,82,82;,
  4;85,85,85,85;,
  4;84,84,84,84;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;82,82,82,82;,
  4;86,86,86,86;,
  4;84,84,84,84;,
  4;111,111,111,111;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;82,82,82,82;,
  4;87,87,87,87;,
  4;84,84,84,84;,
  4;114,114,114,114;,
  4;115,115,115,115;,
  4;116,116,116,116;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;117,117,117,117;,
  4;118,118,118,118;,
  4;119,119,119,119;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;;
 }
 MeshTextureCoords {
  278;
  0.712440;0.713390;,
  0.677030;0.713390;,
  0.677030;0.705800;,
  0.712440;0.705800;,
  0.726520;0.725140;,
  0.771930;0.725140;,
  0.771930;0.734350;,
  0.726520;0.734350;,
  0.712440;0.621430;,
  0.720030;0.621430;,
  0.720030;0.705800;,
  0.786010;0.707510;,
  0.822180;0.707510;,
  0.822180;0.715260;,
  0.786010;0.715260;,
  0.778260;0.707510;,
  0.778260;0.621340;,
  0.786010;0.628680;,
  0.677030;0.621430;,
  0.677030;0.613840;,
  0.712440;0.613840;,
  0.727130;0.596490;,
  0.774150;0.596490;,
  0.774150;0.606030;,
  0.727130;0.606030;,
  0.786010;0.613590;,
  0.822180;0.613590;,
  0.822180;0.628680;,
  0.669440;0.705800;,
  0.669440;0.621430;,
  0.727130;0.542430;,
  0.774150;0.542430;,
  0.774150;0.551970;,
  0.727130;0.551970;,
  0.829940;0.621340;,
  0.829940;0.707510;,
  0.726520;0.777350;,
  0.771930;0.777350;,
  0.771930;0.786570;,
  0.726520;0.786570;,
  0.726430;0.714420;,
  0.726430;0.612690;,
  0.771520;0.612690;,
  0.771520;0.714420;,
  0.727910;0.537450;,
  0.727910;0.438480;,
  0.771780;0.438480;,
  0.771780;0.537450;,
  0.967310;0.348770;,
  0.976060;0.357520;,
  0.956990;0.365420;,
  0.956990;0.353040;,
  0.937920;0.357520;,
  0.946660;0.348770;,
  0.946180;0.373690;,
  0.937430;0.365420;,
  0.956510;0.365420;,
  0.956510;0.373690;,
  0.975580;0.365420;,
  0.966830;0.373690;,
  0.946660;0.328120;,
  0.937920;0.319370;,
  0.956990;0.311470;,
  0.956990;0.323850;,
  0.976060;0.319370;,
  0.967310;0.328120;,
  0.945200;0.373620;,
  0.936450;0.365350;,
  0.955530;0.365350;,
  0.955530;0.373620;,
  0.974600;0.365350;,
  0.965850;0.373620;,
  0.981910;0.363370;,
  0.956990;0.373690;,
  0.932070;0.363370;,
  0.931590;0.353040;,
  0.956510;0.353040;,
  0.981420;0.353040;,
  0.932070;0.313530;,
  0.956990;0.303210;,
  0.981910;0.313530;,
  0.930610;0.352980;,
  0.955530;0.352980;,
  0.980450;0.352980;,
  0.970100;0.363200;,
  0.955500;0.365250;,
  0.955500;0.338280;,
  0.970100;0.338280;,
  0.955500;0.311300;,
  0.970100;0.313360;,
  0.929530;0.338450;,
  0.956510;0.338450;,
  0.983480;0.338450;,
  0.943020;0.315250;,
  0.957620;0.313190;,
  0.957620;0.340170;,
  0.943020;0.340170;,
  0.957620;0.367140;,
  0.943020;0.365090;,
  0.928550;0.338380;,
  0.955530;0.338380;,
  0.982500;0.338380;,
  0.940900;0.363200;,
  0.940900;0.338280;,
  0.940900;0.313360;,
  0.931590;0.323850;,
  0.956510;0.323850;,
  0.981420;0.323850;,
  0.972210;0.315250;,
  0.972210;0.340170;,
  0.972210;0.365090;,
  0.930610;0.323780;,
  0.955530;0.323780;,
  0.980450;0.323780;,
  0.980930;0.313460;,
  0.975090;0.319310;,
  0.956010;0.311410;,
  0.956010;0.303140;,
  0.936940;0.319310;,
  0.931100;0.313460;,
  0.937430;0.311470;,
  0.956510;0.311470;,
  0.975580;0.311470;,
  0.931100;0.363300;,
  0.936940;0.357450;,
  0.956010;0.365350;,
  0.956010;0.373620;,
  0.975090;0.357450;,
  0.980930;0.363300;,
  0.936450;0.311410;,
  0.955530;0.311410;,
  0.974600;0.311410;,
  0.966340;0.328060;,
  0.956010;0.323780;,
  0.945690;0.328060;,
  0.946180;0.303210;,
  0.956510;0.303210;,
  0.966830;0.303210;,
  0.945690;0.348700;,
  0.956010;0.352980;,
  0.966340;0.348700;,
  0.945200;0.303140;,
  0.955530;0.303140;,
  0.965850;0.303140;,
  0.956990;0.338450;,
  0.942390;0.338450;,
  0.971580;0.338450;,
  0.956010;0.338380;,
  0.941420;0.338380;,
  0.970610;0.338380;,
  0.854890;0.738240;,
  0.826050;0.777290;,
  0.818260;0.771040;,
  0.847100;0.731980;,
  0.856340;0.781360;,
  0.815590;0.781360;,
  0.815590;0.775110;,
  0.856340;0.775110;,
  0.818980;0.741190;,
  0.847830;0.780240;,
  0.840040;0.786500;,
  0.811190;0.747440;,
  0.849570;0.786500;,
  0.849570;0.745750;,
  0.855820;0.745750;,
  0.855820;0.786500;,
  0.856340;0.736060;,
  0.815590;0.736060;,
  0.815590;0.742310;,
  0.856340;0.742310;,
  0.863220;0.747870;,
  0.841130;0.771620;,
  0.833820;0.764810;,
  0.855910;0.741070;,
  0.823220;0.741570;,
  0.823220;0.782320;,
  0.815910;0.782320;,
  0.815910;0.741570;,
  0.840010;0.772640;,
  0.817920;0.748900;,
  0.825230;0.742090;,
  0.847320;0.765840;,
  0.854090;0.741570;,
  0.854090;0.782320;,
  0.846780;0.782320;,
  0.846780;0.741570;,
  0.838000;0.741570;,
  0.838000;0.782320;,
  0.845310;0.782320;,
  0.845310;0.741570;,
  0.827620;0.749380;,
  0.848320;0.774350;,
  0.840630;0.780720;,
  0.819930;0.755760;,
  0.851130;0.750300;,
  0.851130;0.791050;,
  0.843440;0.791050;,
  0.843440;0.750300;,
  0.823010;0.765620;,
  0.843720;0.740650;,
  0.851410;0.747030;,
  0.830700;0.771990;,
  0.860410;0.738770;,
  0.860410;0.779520;,
  0.852720;0.779520;,
  0.852720;0.738770;,
  0.822730;0.750300;,
  0.822730;0.791050;,
  0.830420;0.791050;,
  0.830420;0.750300;,
  0.881090;0.900830;,
  0.881090;0.812900;,
  0.906820;0.812900;,
  0.906820;0.900830;,
  0.884470;0.701570;,
  0.884470;0.624550;,
  0.909970;0.624550;,
  0.909970;0.701570;,
  0.881950;0.805980;,
  0.881950;0.711940;,
  0.909470;0.711940;,
  0.909470;0.805980;,
  0.879280;0.994670;,
  0.879280;0.906590;,
  0.908440;0.906590;,
  0.908440;0.994670;,
  0.915470;0.896360;,
  0.915470;0.815260;,
  0.987160;0.815260;,
  0.987160;0.896360;,
  0.801540;0.894340;,
  0.801540;0.814270;,
  0.872310;0.814270;,
  0.872310;0.894340;,
  0.835850;0.789960;,
  0.812150;0.743190;,
  0.822340;0.738030;,
  0.846040;0.784800;,
  0.838190;0.766400;,
  0.838130;0.745360;,
  0.848310;0.745440;,
  0.848370;0.766480;,
  0.813860;0.782750;,
  0.837560;0.735970;,
  0.847740;0.741130;,
  0.824040;0.787900;,
  0.827520;0.769050;,
  0.827580;0.748000;,
  0.837760;0.747930;,
  0.837700;0.768970;,
  0.836450;0.784310;,
  0.835420;0.737540;,
  0.856470;0.737110;,
  0.857490;0.783880;,
  0.811960;0.783880;,
  0.812990;0.737110;,
  0.834030;0.737540;,
  0.833010;0.784310;,
  0.821000;0.738610;,
  0.851500;0.781270;,
  0.842210;0.787900;,
  0.811720;0.745250;,
  0.832150;0.742930;,
  0.853020;0.742800;,
  0.852940;0.752010;,
  0.832080;0.752140;,
  0.812150;0.782810;,
  0.842640;0.740150;,
  0.851930;0.746790;,
  0.821430;0.789450;,
  0.825520;0.773750;,
  0.846390;0.773880;,
  0.846460;0.783090;,
  0.825590;0.782960;,
  0.833090;0.782380;,
  0.853960;0.782250;,
  0.826540;0.743520;,
  0.847400;0.743640;;
 }
}
