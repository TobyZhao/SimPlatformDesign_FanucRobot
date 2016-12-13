function M2r = MotorM2(in1,in2,in3,in4,in5,in6,in7,in8,in9,in10)
%MOTORM2
%    M2R = MOTORM2(IN1,IN2,IN3,IN4,IN5,IN6,IN7,IN8,IN9,IN10)

%    This function was generated by the Symbolic Math Toolbox version 5.5.
%    04-Dec-2014 19:06:27

Cx2 = in10(:,2);
Cx3 = in10(:,3);
Cx4 = in10(:,4);
Cx5 = in10(:,5);
Cx6 = in10(:,6);
Cy2 = in10(:,8);
Cy3 = in10(:,9);
Cy4 = in10(:,10);
Cy5 = in10(:,11);
Cy6 = in10(:,12);
Cz2 = in10(:,14);
Cz3 = in10(:,15);
Cz4 = in10(:,16);
Cz5 = in10(:,17);
Cz6 = in10(:,18);
I2_11 = in5(:,1);
I2_12 = in5(:,4);
I2_21 = in5(:,2);
I2_13 = in5(:,7);
I2_22 = in5(:,5);
I2_31 = in5(:,3);
I2_23 = in5(:,8);
I2_32 = in5(:,6);
I2_33 = in5(:,9);
I3_11 = in6(:,1);
I3_12 = in6(:,4);
I3_21 = in6(:,2);
I3_13 = in6(:,7);
I3_22 = in6(:,5);
I3_31 = in6(:,3);
I3_23 = in6(:,8);
I3_32 = in6(:,6);
I3_33 = in6(:,9);
I4_11 = in7(:,1);
I4_12 = in7(:,4);
I4_21 = in7(:,2);
I4_13 = in7(:,7);
I4_22 = in7(:,5);
I4_31 = in7(:,3);
I4_23 = in7(:,8);
I4_32 = in7(:,6);
I4_33 = in7(:,9);
I5_11 = in8(:,1);
I5_12 = in8(:,4);
I5_21 = in8(:,2);
I5_13 = in8(:,7);
I5_22 = in8(:,5);
I5_31 = in8(:,3);
I5_23 = in8(:,8);
I5_32 = in8(:,6);
I5_33 = in8(:,9);
I6_11 = in9(:,1);
I6_12 = in9(:,4);
I6_21 = in9(:,2);
I6_13 = in9(:,7);
I6_22 = in9(:,5);
I6_31 = in9(:,3);
I6_23 = in9(:,8);
I6_32 = in9(:,6);
I6_33 = in9(:,9);
Ld1 = in2(:,1);
Ld2 = in2(:,2);
Ld3 = in2(:,3);
Ld4 = in2(:,4);
Ld5 = in2(:,5);
Ld6 = in2(:,6);
Ld7 = in2(:,7);
Ma2 = in3(:,2);
Ma3 = in3(:,3);
Ma4 = in3(:,4);
Ma5 = in3(:,5);
Ma6 = in3(:,6);
th2 = in1(:,2);
th3 = in1(:,3);
th4 = in1(:,4);
th5 = in1(:,5);
th6 = in1(:,6);
t1842 = cos(th6);
t1854 = pi.*(1.0./2.0);
t1843 = -t1854+th2;
t1844 = sin(th3);
t1845 = sin(th4);
t1846 = sin(th6);
t1847 = t1845.*t1846;
t1848 = cos(th4);
t1849 = cos(th5);
t1909 = t1842.*t1848.*t1849;
t1850 = t1847-t1909;
t1851 = cos(th3);
t1852 = sin(th5);
t1855 = cos(t1843);
t1856 = sin(t1843);
t1910 = t1850.*t1844;
t1911 = t1842.*t1851.*t1852;
t1912 = t1910-t1911;
t1913 = t1850.*t1851;
t1914 = t1842.*t1852.*t1844;
t1915 = t1913+t1914;
t1916 = t1855.*t1915;
t1917 = t1856.*t1912;
t1853 = t1916-t1917;
t1857 = t1842.*t1845;
t1858 = t1846.*t1848.*t1849;
t1859 = t1857+t1858;
t1886 = t1844.*t1859;
t1887 = t1851.*t1852.*t1846;
t1888 = t1886+t1887;
t1889 = t1851.*t1859;
t1890 = t1852.*t1844.*t1846;
t1891 = t1890-t1889;
t1892 = t1855.*t1891;
t1893 = t1856.*t1888;
t1860 = -t1892-t1893;
t1904 = t1844.*t1856.*t1848;
t1905 = t1851.*t1855.*t1848;
t1861 = -t1904+t1905;
t1863 = t1851.*t1845.*t1855;
t1864 = t1844.*t1845.*t1856;
t1862 = t1863-t1864;
t1865 = t1862.^2;
t1868 = t1851.*t1856;
t1869 = t1844.*t1855;
t1866 = t1868+t1869;
t1884 = t1851.*t1855;
t1885 = t1844.*t1856;
t1867 = t1884-t1885;
t1870 = t1866.^2;
t1871 = cos(th2);
t1874 = t1844.*t1849;
t1875 = t1851.*t1852.*t1848;
t1876 = t1874+t1875;
t1877 = t1855.*t1876;
t1878 = t1851.*t1849;
t1879 = t1852.*t1844.*t1848;
t1880 = t1878-t1879;
t1881 = t1880.*t1856;
t1872 = t1881+t1877;
t1894 = t1852.*t1844;
t1895 = t1851.*t1848.*t1849;
t1896 = t1894-t1895;
t1897 = t1855.*t1896;
t1898 = t1851.*t1852;
t1899 = t1844.*t1848.*t1849;
t1900 = t1898+t1899;
t1901 = t1856.*t1900;
t1873 = t1897+t1901;
t1882 = t1872.^2;
t1883 = sin(th2);
t1902 = t1880.*t1855;
t1930 = t1856.*t1876;
t1903 = t1902-t1930;
t1906 = t1851.*t1845.*t1856;
t1907 = t1844.*t1845.*t1855;
t1908 = t1906+t1907;
t1918 = t1904-t1905;
t1919 = -Cz4+Ld1+Ld2+Ld4+Ld6;
t1920 = -Cx6+Ld3+Ld7;
t1921 = -Cx5+Ld3+Ld7;
t1922 = Cx4-Ld3;
t1923 = Cy4-Ld5;
t1924 = Cy6-Ld5;
t1925 = -Cz6+Ld1+Ld2+Ld4+Ld6;
t1926 = -Cz5+Ld1+Ld2+Ld4+Ld6;
t1927 = Cy5-Ld5;
t1928 = t1856.*t1896;
t1971 = t1855.*t1900;
t1929 = -t1971+t1928;
t1931 = Ld4.*t1856;
t1932 = Ld7.*t1851;
t1933 = Ld6.*t1844;
t1934 = t1932+t1933;
t1935 = t1855.*t1934;
t1936 = Ld6.*t1851;
t1941 = Ld7.*t1844;
t1937 = -t1941+t1936;
t1938 = t1856.*t1937;
t1939 = t1931+t1935+t1938;
t1940 = Ld5.*t1903;
t2018 = t1852.*t1845.*t1939;
t1942 = t1940-t2018;
t1943 = t1846.*t1848;
t1944 = t1842.*t1845.*t1849;
t1945 = t1943+t1944;
t1946 = t1855.*t1912;
t1947 = t1856.*t1915;
t1948 = t1946+t1947;
t1949 = t1842.*t1848;
t1988 = t1845.*t1846.*t1849;
t1950 = t1949-t1988;
t1951 = t1891.*t1856;
t1952 = t1851.*t1856.*t1848;
t1953 = t1844.*t1855.*t1848;
t1954 = t1952+t1953;
t1955 = Ld6.*t1851.*t1856;
t1956 = Ld6.*t1844.*t1855;
t1957 = t1931+t1955+t1956;
t1958 = Ld5.*t1908;
t1959 = Ma6.*t1853.*t1920;
t1992 = Ma6.*t1872.*t1925;
t1960 = -t1992+t1959;
t1961 = Ma5.*t1873.*t1921;
t1993 = Ma5.*t1872.*t1926;
t1962 = t1961-t1993;
t1963 = Ma4.*t1922.*t1918;
t1964 = Ma4.*t1866.*t1919;
t1965 = t1963+t1964;
t1966 = Ma4.*t1862.*t1919;
t1967 = Ma6.*t1860.*t1920;
t1994 = Ma6.*t1872.*t1924;
t1968 = t1967-t1994;
t1969 = Ma5.*t1862.*t1921;
t1995 = Ma5.*t1872.*t1927;
t1970 = -t1995+t1969;
t1972 = Ma4.*t1862.*t1922;
t1973 = Ma4.*t1866.*t1923;
t1974 = t1972+t1973;
t1975 = Ma6.*t1860.*t1925;
t1976 = Ma5.*t1862.*t1926;
t2002 = Ma5.*t1873.*t1927;
t1977 = t1976-t2002;
t1978 = t1867.^2;
t1979 = t1871.^2;
t1980 = Ld4.*t1855;
t1981 = t1855.*t1937;
t1984 = t1856.*t1934;
t1982 = t1980+t1981-t1984;
t1983 = Ld5.*t1872;
t1985 = t1852.*t1845.*t1982;
t1986 = t1983+t1985;
t1987 = t1883.^2;
t1989 = Ld6.*t1851.*t1855;
t1996 = Ld6.*t1844.*t1856;
t1990 = t1980-t1996+t1989;
t1991 = Ld5.*t1862;
t1997 = t1971-t1928;
t1998 = t1903.*t1982;
t1999 = t1872.*t1939;
t2000 = t1998+t1999;
t2003 = t1855.*t1888;
t2001 = t1951-t2003;
t2004 = Ma4.*t1862.*t1908;
t2005 = Ma5.*t1862.*t1908;
t2006 = Ma6.*t1853.*t1948;
t2007 = t1951-t2003;
t2008 = t1908.^2;
t2009 = Ma3.*t1870;
t2010 = Ma3.*t1978;
t2011 = Ma2.*t1979;
t2012 = t1903.^2;
t2013 = Ma2.*t1987;
t2014 = Cy3.*Ma3.*t1870;
t2015 = Cy3.*Ma3.*t1978;
t2016 = Cy2.*Ma2.*t1979;
t2017 = Cy2.*Ma2.*t1987;
t2019 = Ld5.*t1948;
t2104 = t1945.*t1939;
t2020 = t2019-t2104;
t2106 = t1848.*t1939;
t2021 = t1958-t2106;
t2022 = t1950.*t1939;
t2023 = -t1951+t2003;
t2024 = Ld5.*t1954;
t2025 = t1845.*t1957;
t2026 = t2024+t2025;
t2102 = t1848.*t1957;
t2027 = t1958-t2102;
t2028 = Ma6.*t1920.*t1948;
t2029 = Ma6.*t1903.*t1925;
t2030 = t2028+t2029;
t2031 = Ma5.*t1903.*t1926;
t2057 = Ma5.*t1921.*t1997;
t2032 = t2031-t2057;
t2033 = Ma4.*t1922.*t1954;
t2034 = Ma4.*t1867.*t1919;
t2035 = t2033+t2034;
t2036 = Ma4.*t1923.*t1954;
t2037 = Ma4.*t1908.*t1919;
t2038 = t2036+t2037;
t2039 = Ma6.*t1903.*t1924;
t2040 = Ma5.*t1921.*t1908;
t2041 = Ma5.*t1903.*t1927;
t2042 = t2040+t2041;
t2043 = Ma4.*t1867.*t1923;
t2060 = Ma4.*t1922.*t1908;
t2044 = -t2060+t2043;
t2045 = Ma6.*t1924.*t1948;
t2046 = Ma5.*t1908.*t1926;
t2047 = Ma5.*t1927.*t1997;
t2048 = t2046+t2047;
t2049 = Ld5.*t1873;
t2131 = t1845.*t1849.*t1982;
t2050 = t2049-t2131;
t2051 = Ld5.*t1853;
t2129 = t1848.*t1982;
t2052 = t1991-t2129;
t2053 = Ld5.*t1860;
t2054 = Ld5.*t1918;
t2128 = t1845.*t1990;
t2055 = t2054-t2128;
t2056 = Ld5.*Ma4.*t1866.*t1867;
t2058 = Ma6.*t1920.*t2023;
t2059 = t2039+t2058;
t2061 = -Cz2+Ld1+Ld2;
t2062 = t1853.*t1939;
t2134 = t1982.*t1948;
t2063 = t2062-t2134;
t2064 = t1862.*t1957;
t2135 = t1908.*t1990;
t2065 = t2064-t2135;
t2066 = -Cz3+Ld1+Ld2+Ld4;
t2067 = Ld4.*t1855.*t1867;
t2068 = Ld4.*t1856.*t1866;
t2069 = t2067+t2068;
t2070 = Ld4.*t1855.*t1866;
t2308 = Ld4.*t1856.*t1867;
t2071 = t2070-t2308;
t2072 = t1862.*t1939;
t2136 = t1908.*t1982;
t2073 = t2072-t2136;
t2074 = t1982.*t1997;
t2075 = t1873.*t1939;
t2076 = t2074+t2075;
t2077 = t1860.*t1939;
t2078 = Cx3-Ld3;
t2309 = Ma6.*t1925.*t2023;
t2079 = t2045-t2309;
t2080 = Cx2-Ld3;
t2081 = t1867.*t1990;
t2082 = t1866.*t1957;
t2083 = t2081+t2082;
t2084 = t1954.*t1990;
t2085 = t1918.*t1957;
t2086 = t2084+t2085;
t2087 = Ma4.*t1845.*t1918;
t2088 = Ma4.*t1862.*t1848;
t2089 = Ma5.*t1862.*t1848;
t2090 = Ma6.*t1853.*t1945;
t2091 = Ma6.*t1860.*t1950;
t2092 = Ma5.*t1845.*t1873.*t1849;
t2093 = t2090+t2091+t2092+t2087+t2088+t2089-Ma5.*t1852.*t1845.*t1872-Ma6.*t1852.*t1845.*t1872;
t2094 = Ma4.*t1848.*t1908;
t2095 = Ma5.*t1848.*t1908;
t2096 = Ma6.*t1945.*t1948;
t2097 = Ma5.*t1852.*t1845.*t1903;
t2098 = Ma6.*t1852.*t1845.*t1903;
t2099 = t1848.^2;
t2100 = t1845.^2;
t2101 = t1852.^2;
t2103 = Ma3.*t1866.*t2066;
t2138 = Ld5.*t2023;
t2105 = t2022-t2138;
t2107 = Ld5.*t1997;
t2108 = t1845.*t1849.*t1939;
t2109 = t2107+t2108;
t2110 = Ma5.*t1845.*t1849.*t1921;
t2111 = Ma5.*t1852.*t1845.*t1926;
t2112 = t2110+t2111;
t2113 = Ma4.*t1845.*t1923;
t2403 = Ma4.*t1848.*t1919;
t2114 = t2113-t2403;
t2115 = Ma5.*t1848.*t1926;
t2132 = Ma5.*t1845.*t1849.*t1927;
t2116 = -t2132+t2115;
t2117 = Ma6.*t1920.*t1950;
t2118 = Ma6.*t1852.*t1845.*t1924;
t2119 = t2117+t2118;
t2120 = Ma6.*t1950.*t1925;
t2133 = Ma6.*t1924.*t1945;
t2121 = t2120-t2133;
t2122 = Ma6.*t1920.*t1945;
t2123 = Ma6.*t1852.*t1845.*t1925;
t2124 = t2122+t2123;
t2125 = Ma5.*t1848.*t1921;
t2126 = Ma5.*t1852.*t1845.*t1927;
t2127 = t2125+t2126;
t2130 = Ma2.*t1871.*t2080;
t2297 = t1982.*t2023;
t2137 = t2077-t2297;
t2139 = Ld5.*Ma4.*t1867;
t2194 = Ma4.*t1923.*t1918;
t2140 = t1966+t2139-t2194;
t2141 = Ma6.*t1942;
t2158 = Ma6.*t1853.*t1924;
t2142 = t1975+t2141-t2158;
t2143 = Ma5.*t2021;
t2144 = -t1961+t1993+t2143;
t2145 = Ma5.*t1942;
t2146 = t1976-t2002+t2145;
t2147 = Ma6.*t2020;
t2148 = t1967-t1994+t2147;
t2149 = Ma6.*t2105;
t2150 = -t1992+t1959+t2149;
t2151 = Ma5.*t2109;
t2152 = t1995-t1969+t2151;
t2153 = Ma4.*t2027;
t2154 = t1963+t1964+t2153;
t2155 = Ma4.*t2026;
t2156 = t1972+t1973+t2155;
t2157 = Ma2.*t1871.*t2061;
t2159 = Ma3.*t1867.*t2078;
t2160 = Ma2.*t1883.*t2080;
t2161 = Ld4.*Ma3.*t1856;
t2162 = t1920.^2;
t2163 = Ma6.*t2162;
t2164 = Ma6.*t1924.*t1925;
t2165 = t1927.^2;
t2166 = Ma5.*t2165;
t2167 = t1919.^2;
t2168 = Ma4.*t2167;
t2169 = Cy3.^2;
t2170 = Ma3.*t2169;
t2171 = Ma3.*t2066.*t2078;
t2172 = t1922.^2;
t2173 = Ma4.*t2172;
t2174 = t1923.^2;
t2175 = Ma4.*t2174;
t2176 = Ma4.*t1923.*t1919;
t2177 = Ma4.*t1922.*t1919;
t2178 = t1925.^2;
t2179 = Ma6.*t2178;
t2180 = t1924.^2;
t2181 = Ma6.*t2180;
t2182 = Ma6.*t1920.*t1924;
t2183 = Ma5.*t1926.*t1927;
t2184 = t1926.^2;
t2185 = Ma5.*t2184;
t2186 = t1921.^2;
t2187 = Ma5.*t2186;
t2188 = Ma5.*t1921.*t1927;
t2189 = Ma2.*t2061.*t2080;
t2190 = Cy2.^2;
t2191 = Ma2.*t2190;
t2192 = -t2019+t2104;
t2193 = -t1958+t2102;
t2195 = t2066.^2;
t2196 = Ma3.*t2195;
t2197 = I3_11+t2170+t2196;
t2198 = I3_31+t2171;
t2199 = t1867.*t2198;
t2200 = Ld4.*Ma3.*t1856.*t2066;
t2201 = t2199+t2200-t1866.*t2197;
t2202 = I2_31+t2189;
t2203 = t1883.*t2202;
t2204 = t2061.^2;
t2205 = Ma2.*t2204;
t2206 = I2_11+t2191+t2205;
t2207 = t1871.*t2206;
t2208 = t2203+t2207;
t2229 = Ma5.*t1921.*t1926;
t2209 = I5_13-t2229;
t2210 = I5_23+t2183;
t2211 = t1862.*t2210;
t2212 = I5_33+t2166+t2187;
t2213 = Ma5.*t1921.*t2021;
t2214 = Ma5.*t1942.*t1927;
t2306 = t1872.*t2209;
t2307 = t1873.*t2212;
t2215 = t2211+t2213+t2214-t2306-t2307;
t2216 = I6_22+t2163+t2179;
t2217 = t1860.*t2216;
t2218 = I6_32+t2164;
t2219 = I6_12+t2182;
t2220 = Ma6.*t1942.*t1925;
t2221 = I6_33+t2163+t2181;
t2222 = t1853.*t2221;
t2266 = Ma6.*t1920.*t1925;
t2223 = I6_13-t2266;
t2224 = t1872.*t2223;
t2225 = I6_23+t2164;
t2226 = Ma6.*t1920.*t2105;
t2295 = t1860.*t2225;
t2296 = Ma6.*t1924.*t1942;
t2227 = t2222+t2224+t2226-t2295-t2296;
t2228 = I5_21+t2188;
t2230 = I5_11+t2166+t2185;
t2231 = t1872.*t2230;
t2232 = Ma5.*t1926.*t2021;
t2233 = Ma5.*t1927.*t2109;
t2234 = I2_13+t2189;
t2235 = t1871.*t2234;
t2236 = t2080.^2;
t2237 = Ma2.*t2236;
t2238 = I2_33+t2191+t2237;
t2239 = t1883.*t2238;
t2240 = t2235+t2239;
t2241 = I4_11+t2175+t2168;
t2242 = t1866.*t2241;
t2243 = I4_31+t2177;
t2244 = t1918.*t2243;
t2247 = Ma4.*t1922.*t1923;
t2245 = I4_21-t2247;
t2246 = Ma4.*t1923.*t2026;
t2248 = I4_22+t2173+t2168;
t2249 = t1862.*t2248;
t2250 = I4_32+t2176;
t2251 = Ma4.*t1922.*t2026;
t2252 = Ld5.*Ma4.*t1867.*t1919;
t2253 = t2078.^2;
t2254 = Ma3.*t2253;
t2255 = I3_33+t2170+t2254;
t2256 = t1867.*t2255;
t2257 = I3_13+t2171;
t2258 = Ld4.*Ma3.*t1856.*t2078;
t2259 = t2256+t2258-t1866.*t2257;
t2260 = I4_33+t2173+t2175;
t2261 = t1918.*t2260;
t2262 = I4_23+t2176;
t2263 = I4_13+t2177;
t2264 = t1866.*t2263;
t2265 = I6_11+t2181+t2179;
t2267 = I6_21+t2182;
t2268 = t1860.*t2267;
t2269 = Ma6.*t1925.*t2105;
t2270 = I5_32+t2183;
t2271 = t1873.*t2270;
t2272 = I5_22+t2185+t2187;
t2273 = I5_12+t2188;
t2274 = t1872.*t2273;
t2275 = Ma5.*t1921.*t2109;
t2284 = t1862.*t2272;
t2285 = Ma5.*t1942.*t1926;
t2276 = t2271+t2274+t2275-t2284-t2285;
t2277 = Ma6.*t2192;
t2278 = -t1967+t1994+t2277;
t2286 = Ma4.*t2193;
t2279 = t1963+t1964-t2286;
t2311 = t1848.*t1990;
t2280 = t1991-t2311;
t2281 = -t2103+t2161+t2159;
t2282 = I4_12-t2247;
t2283 = t2251+t2252+t2249-t1866.*t2282-t1918.*t2250;
t2287 = t1862.*t2262;
t2288 = Ma4.*t1922.*t2193;
t2289 = Ld5.*Ma4.*t1867.*t1923;
t2290 = -t2261-t2264+t2287+t2288+t2289;
t2291 = t1853.*t2218;
t2292 = t1872.*t2219;
t2293 = Ma6.*t1920.*t2192;
t2294 = -t2220-t2217+t2291+t2292+t2293;
t2298 = I5_31-t2229;
t2299 = t1873.*t2298;
t2300 = t2231+t2232+t2233+t2299-t1862.*t2228;
t2301 = t1872.*t2265;
t2302 = I6_31-t2266;
t2303 = t1853.*t2302;
t2304 = Ma6.*t1924.*t2192;
t2305 = -t2268-t2269+t2301+t2303+t2304;
t2320 = t1945.*t1982;
t2310 = t2051-t2320;
t2312 = Ld5.*Ma4.*t1866;
t2313 = t2036+t2037+t2312;
t2314 = Ma6.*t1986;
t2315 = -t2045+t2314+t2309;
t2316 = Ma5.*t2052;
t2317 = t2031-t2057+t2316;
t2318 = Ma5.*t1986;
t2319 = t2046+t2047+t2318;
t2330 = Ma6.*t2310;
t2321 = t2039+t2058-t2330;
t2329 = t1950.*t1982;
t2335 = t2053-t2329;
t2322 = Ma6.*t2335;
t2323 = t2028+t2029+t2322;
t2333 = Ma5.*t2050;
t2324 = t2040+t2041-t2333;
t2325 = Ma4.*(t1991-t2311);
t2326 = t2033+t2034+t2325;
t2327 = Ma4.*t2055;
t2328 = t2060-t2043+t2327;
t2331 = Ma2.*t1883.*t2061;
t2332 = Ma3.*t1867.*t2066;
t2334 = Ma3.*t1866.*t2078;
t2336 = t1871.*t2202;
t2337 = t2336-t1883.*t2206;
t2338 = t2023.*t2216;
t2339 = t1903.*t2219;
t2340 = Ma6.*t1925.*t1986;
t2394 = t1948.*t2218;
t2341 = t2340+t2338+t2339-t2394-Ma6.*t1920.*t2310;
t2342 = t1903.*t2223;
t2343 = t2023.*t2225;
t2344 = Ma6.*t1924.*t1986;
t2399 = t1948.*t2221;
t2345 = t2342+t2343+t2344-t2399-Ma6.*t1920.*t2335;
t2346 = t1908.*t2228;
t2347 = t1997.*t2298;
t2348 = t1903.*t2230;
t2349 = Ma5.*t1926.*t2052;
t2401 = Ma5.*t1927.*t2050;
t2350 = t2346+t2347+t2348+t2349-t2401;
t2351 = t1867.*t2241;
t2352 = t1954.*t2243;
t2353 = t1908.*t2245;
t2354 = t1883.*t2234;
t2355 = t2354-t1871.*t2238;
t2356 = t1903.*t2265;
t2357 = t2023.*t2267;
t2358 = t1867.*t2282;
t2359 = t1908.*t2248;
t2360 = t1954.*t2250;
t2361 = Ma4.*t1922.*t2055;
t2362 = Ld5.*Ma4.*t1866.*t1919;
t2363 = t2360+t2361+t2362+t2358+t2359;
t2364 = t1997.*t2270;
t2365 = t1908.*t2272;
t2366 = t1903.*t2273;
t2367 = Ma5.*t1926.*t1986;
t2389 = Ma5.*t1921.*t2050;
t2368 = t2364+t2365+t2366+t2367-t2389;
t2369 = t1866.*t2255;
t2370 = t1867.*t2257;
t2371 = t2370+t2369-Ld4.*Ma3.*t1855.*t2078;
t2372 = t1954.*t2260;
t2373 = t1908.*t2262;
t2374 = t1867.*t2263;
t2375 = Ld5.*Ma4.*t1866.*t1923;
t2376 = -t2051+t2320;
t2377 = -t1991+t2311;
t2378 = -t2053+t2329;
t2379 = t1867.*t2197;
t2380 = t1866.*t2198;
t2381 = t2380+t2379-Ld4.*Ma3.*t1855.*t2066;
t2382 = t1903.*t2209;
t2383 = t1908.*t2210;
t2384 = t1997.*t2212;
t2385 = Ma5.*t1927.*t1986;
t2402 = Ma5.*t1921.*t2052;
t2386 = t2382+t2383+t2384+t2385-t2402;
t2387 = t2332+t2334-Ld4.*Ma3.*t1855;
t2428 = Cy3.*Ma3.*t2078;
t2388 = I3_12-t2428;
t2429 = Cy2.*Ma2.*t2080;
t2390 = I2_12-t2429;
t2391 = t2033+t2034-Ma4.*t2377;
t2392 = Cy2.*Ma2.*t2061;
t2393 = I2_32+t2392;
t2395 = Cy3.*Ma3.*t2066;
t2396 = I3_32+t2395;
t2397 = Ma6.*t2376;
t2398 = t2039+t2058+t2397;
t2400 = t2028+t2029-Ma6.*t2378;
t2404 = Ma6.*t2000;
t2405 = -t2120+t2133+t2404;
t2406 = Ma3.*t2071;
t2474 = Ma3.*t2078;
t2407 = t2406-t2474;
t2408 = Ma5.*t2076;
t2409 = t2125+t2126+t2408;
t2410 = Ma4.*t2083;
t2411 = t2113+t2410-t2403;
t2412 = Ma4.*t2086;
t2427 = Ma4.*t1848.*t1922;
t2413 = t2412-t2427;
t2414 = Ma6.*t2063;
t2415 = t2117+t2118+t2414;
t2416 = Ma5.*t2000;
t2417 = t2132-t2115+t2416;
t2426 = Ma6.*t2137;
t2418 = t2122+t2123-t2426;
t2419 = Ma3.*t2066;
t2469 = Ma3.*t2069;
t2420 = t2419-t2469;
t2425 = Ma5.*t2073;
t2421 = t2110+t2111-t2425;
t2422 = Ma4.*t2065;
t2423 = Ma4.*t1845.*t1922;
t2424 = t2422+t2423;
t2430 = Cy3.*Ma3.*t2071;
t2431 = I3_21+t2430-t2428;
t2432 = t1845.*t2250;
t2433 = Ma4.*t1919.*t2083;
t2434 = Ma4.*t1922.*t2086;
t2473 = t1848.*t2248;
t2435 = t2432+t2433+t2434-t2473;
t2436 = t1950.*t2216;
t2437 = t1852.*t1845.*t2219;
t2438 = Ma6.*t1920.*t2063;
t2471 = t1945.*t2218;
t2472 = Ma6.*t1925.*t2000;
t2439 = -t2471+t2436-t2472+t2437+t2438;
t2440 = t1950.*t2267;
t2441 = Ma6.*t1924.*t2063;
t2442 = t1852.*t1845.*t2265;
t2481 = t1945.*t2302;
t2443 = t2440+t2441+t2442-t2481-Ma6.*t1925.*t2137;
t2444 = I2_21-t2429;
t2445 = t1950.*t2225;
t2446 = t1852.*t1845.*t2223;
t2447 = Ma6.*t1920.*t2137;
t2475 = t1945.*t2221;
t2476 = Ma6.*t1924.*t2000;
t2448 = t2445+t2446+t2447-t2475-t2476;
t2449 = t1848.*t2210;
t2450 = t1852.*t1845.*t2209;
t2451 = Ma5.*t1921.*t2073;
t2452 = t1845.*t2260;
t2453 = Ma4.*t1922.*t2065;
t2454 = Ma4.*t1923.*t2083;
t2480 = t1848.*t2262;
t2455 = t2452+t2453-t2480+t2454;
t2456 = I2_23+t2392;
t2457 = t1845.*t2243;
t2458 = Ma4.*t1919.*t2065;
t2459 = t2457+t2458-t1848.*t2245-Ma4.*t1923.*t2086;
t2460 = t1848.*t2272;
t2461 = Ma5.*t1921.*t2076;
t2462 = t1852.*t1845.*t2273;
t2478 = Ma5.*t1926.*t2000;
t2479 = t1845.*t1849.*t2270;
t2463 = t2460+t2461+t2462-t2478-t2479;
t2464 = I3_23+t2395-Cy3.*Ma3.*t2069;
t2465 = t1848.*t2228;
t2466 = t1852.*t1845.*t2230;
t2467 = Ma5.*t1927.*t2076;
t2482 = t1845.*t1849.*t2298;
t2468 = -t2482+t2465+t2466+t2467-Ma5.*t1926.*t2073;
t2470 = -t2077+t2297;
t2477 = -t2072+t2136;
M2r = reshape([t2010+t2011+t2013+t2009+Ma4.*t1870+Ma4.*t1865+Ma5.*t1882+Ma5.*t1865+Ma6.*t1882+Ma4.*t1861.^2+Ma5.*t1873.^2+Ma6.*t1860.^2+Ma6.*t1853.^2,t2004+t2005+t2006-Ma4.*t1866.*t1867-Ma5.*t1872.*t1903-Ma4.*t1918.*t1954-Ma5.*t1873.*t1997-Ma6.*t1872.*t1903-Ma6.*t1860.*t2001,t2093,t1860.*t2150+t1872.*t2142-t1862.*t2144+t1866.*t2140-t1862.*t2154+t1873.*t2152+t1872.*t2146-t1853.*t2148+t1918.*t2156,t2014+t2015+t2016+t2017+t1860.*t2323-t1853.*t2321+t1872.*t2315+t1862.*t2317+t1862.*t2326-t1873.*t2324+t1866.*t2313+t1872.*t2319+t1918.*t2328,-t2160-t2157+t1862.*t2421-t1853.*t2415-t1862.*t2424-t1872.*t2405-t1866.*t2411+t1866.*t2420+t1860.*t2418-t1872.*t2417-t1873.*t2409+t1867.*t2407-t1918.*t2413,t2004+t2005+t2006-Ma4.*t1866.*t1867-Ma5.*t1872.*t1903-Ma4.*t1918.*t1954+Ma5.*t1873.*t1929-Ma6.*t1872.*t1903-Ma6.*t1860.*t2001,t2010+t2011+t2013+t2009+Ma4.*t1978+Ma4.*t2008+Ma5.*t2012+Ma5.*t2008+Ma6.*t2012+Ma4.*t1954.^2+Ma5.*t1997.^2+Ma6.*t1948.^2+Ma6.*t2007.^2,t2094+t2095+t2096+t2097+t2098-Ma4.*t1845.*t1954+Ma6.*t1950.*t2023-Ma5.*t1845.*t1849.*t1997,-t2014-t2015-t2016-t2017-t1867.*t2140-t1903.*t2142-t1903.*t2146-t1908.*t2144-t1908.*t2154-t1954.*t2156-t1997.*t2152-t1948.*t2148+t2023.*t2150,-t1867.*t2313-t1903.*t2315-t1903.*t2319-t1948.*t2321+t1908.*t2317+t1908.*t2326-t1954.*t2328+t1997.*t2324+t2023.*t2323,t2130-t2331+t1867.*t2411-t1867.*t2420+t1866.*t2407+t1903.*t2405+t1903.*t2417+t1908.*t2421+t1954.*t2413-t1908.*t2424-t1948.*t2415+t1997.*t2409+t2023.*t2418,t2093,t2094+t2095+t2096+t2097+t2098-Ma4.*t1845.*t1954-Ma6.*t1950.*t2001-Ma5.*t1845.*t1849.*t1997,Ma2+Ma3+Ma4.*t2099+Ma4.*t2100+Ma5.*t2099+Ma6.*t1950.^2+Ma6.*t1945.^2+Ma5.*t2100.*t2101+Ma6.*t2100.*t2101+Ma5.*t1849.^2.*t2100,-t2103+t2160+t2161+t2157+t2159+t1845.*t2156-t1848.*t2144-t1848.*t2154+t1950.*t2150-t1945.*t2148-t1852.*t1845.*t2142-t1852.*t1845.*t2146+t1845.*t1849.*t2152,-t2130+t2331+t2332+t2334+t1845.*t2328+t1848.*t2317+t1848.*t2326+t1950.*t2323-t1945.*t2321-Ld4.*Ma3.*t1855-t1852.*t1845.*t2315-t1852.*t1845.*t2319-t1845.*t1849.*t2324,-t1845.*t2413+t1848.*t2421-t1848.*t2424+t1950.*t2418-t1945.*t2415+t1852.*t1845.*t2405+t1852.*t1845.*t2417-t1845.*t1849.*t2409,t2056-t1866.*(t1966-Ma4.*t1923.*t1918)-t1872.*(t1975-Ma6.*t1853.*t1924)-t1860.*t1960-t1862.*t1962+t1873.*t1970+t1862.*t1965+t1853.*t1968-t1872.*t1977-t1918.*t1974+Ma6.*t1860.*(t2022+Ld5.*t2001)-Ma5.*t1873.*(Ld5.*t1929-t1845.*t1849.*t1939)+Ma5.*t1872.*t1942+Ma6.*t1872.*t1942-Ma4.*t1862.*t2027-Ma5.*t1862.*t2021+Ma4.*t1918.*t2026-Ma6.*t1853.*t2020,-t2014-t2015-t2016-t2017+t1853.*(t2039-Ma6.*t1920.*t2001)-t1860.*t2030-t1862.*t2032-t1862.*t2035+t1873.*t2042-t1872.*t2048-t1866.*t2038+t1918.*t2044+t1872.*(t2045+Ma6.*t1925.*(t1951-t2003))-Ld5.*Ma4.*t1978-Ma5.*t1903.*t1942-Ma6.*t1903.*t1942-Ma4.*t1908.*t2027-Ma4.*t1954.*t2026-Ma5.*t1908.*t2021-Ma6.*t1948.*t2020-Ma5.*t1997.*t2109+Ma6.*t2023.*t2105,-t2103+t2160+t2161+t2157+t2159-t1862.*t2112-t1860.*t2124-t1872.*t2121-t1872.*t2116+t1866.*t2114+t1853.*t2119+t1873.*t2127+Ma4.*t1845.*t2026-Ma4.*t1848.*t2027-Ma5.*t1848.*t2021-Ma6.*t1945.*t2020+Ma6.*t1950.*t2105+Ma4.*t1862.*t1845.*t1922-Ma5.*t1852.*t1845.*t1942-Ma4.*t1848.*t1922.*t1918-Ma6.*t1852.*t1845.*t1942+Ma5.*t1845.*t1849.*t2109,-t1872.*(t2268+t2269-t1853.*(I6_31-Ma6.*t1920.*t1925)-t1872.*t2265+Ma6.*t1924.*t2020)+t1860.*(t2220+t2217-t1853.*t2218-t1872.*t2219+Ma6.*t1920.*t2020)+t1942.*t2142-t1866.*t2201+t1883.*t2240+t1871.*t2208-t1873.*t2215+t1942.*t2146+t1853.*t2227-t1862.*t2276+t1867.*t2259+t2021.*t2144+t2026.*t2156+t2105.*t2150+t2152.*t2109+t2192.*t2278-t2193.*t2279+t1866.*(t2242+t2244+t2246-t1862.*t2245+Ma4.*t1919.*(t1958-t2102))+t1918.*(t2261+t2264-t1862.*t2262+Ma4.*t1922.*t2027-Ld5.*Ma4.*t1867.*t1923)+t1862.*(t2251+t2252+t2249-t1866.*(I4_12-Ma4.*t1922.*t1923)-t1918.*t2250)+t1872.*(t2231+t2232+t2233+t1873.*(I5_31-Ma5.*t1921.*t1926)-t1862.*t2228)+Ld5.*t1867.*t2140+Ld4.*t1856.*t2281,t1860.*t2341-t1872.*t2350-t1853.*t2345+t1862.*t2363-t1871.*t2337+t1883.*t2355-t1866.*t2381+t1867.*t2371+t1862.*t2368-t1873.*t2386+t1942.*t2315+t1942.*t2319-t2021.*t2317+t2026.*t2328-t2192.*t2321-t2109.*t2324+t2193.*t2326+t2105.*(t2028+t2029+Ma6.*(t2053-t2329))-t1872.*(t2356+t2357-t1948.*t2302-Ma6.*t1924.*t2310+Ma6.*t1925.*t2335)-t1918.*(t2372+t2373+t2374+t2375+Ma4.*t1922.*t2280)-t1866.*(t2351+t2352+t2353-Ma4.*t1923.*t2055+Ma4.*t1919.*t2280)+Ld4.*t1856.*t2387+Ld5.*t1867.*t2313,-t1862.*t2435+t1871.*t2444-t1872.*t2443-t1866.*t2431+t1862.*t2463+t1860.*t2439-t1853.*t2448+t1883.*t2456-t1872.*t2468+t1867.*t2464+t1866.*t2459-t1942.*t2405-t1942.*t2417+t1918.*t2455-t2021.*t2421-t2026.*t2413+t2105.*t2418-t2192.*t2415-t2109.*t2409-t2193.*t2424-t1873.*(t2450+t2451+t2449-Ma5.*t1927.*t2000-t1845.*t1849.*t2212)-Ld5.*t1867.*t2411,t2014+t2015+t2016+t2017+t1867.*(t1966-Ma4.*t1923.*t1918)+t1903.*(t1975-Ma6.*t1853.*t1924)-t1908.*t1962+t1903.*t1977+t1908.*t1965+t1954.*t1974-t1970.*t1997+t1948.*t1968+t1960.*t2001+Ma6.*t1860.*(t2053-t1950.*t1982)+Ld5.*Ma4.*t1870+Ma5.*t1872.*t1986+Ma6.*t1872.*t1986+Ma5.*t1862.*t2052+Ma5.*t1873.*t2050+Ma4.*t1918.*t2055+Ma4.*t1862.*t2280+Ma6.*t1853.*t2310,-t2056+t1867.*t2038-t1908.*t2032+t1903.*t2048-t1908.*t2035-t1954.*t2044-t1903.*t2079-t1997.*t2042+t1948.*t2059-t2030.*t2023+Ma6.*t2023.*(t2053-t1950.*t1982)-Ma5.*t1903.*t1986-Ma6.*t1903.*t1986-Ma4.*t1954.*t2055+Ma5.*t1908.*t2052-Ma5.*t1997.*t2050+Ma4.*t1908.*t2280+Ma6.*t1948.*t2310,-t2130+t2331+t2332+t2334-t1867.*t2114+t1903.*t2121+t1903.*t2116-t1908.*t2112+t1948.*t2119-t1997.*t2127-t2023.*t2124+Ma6.*t1950.*(t2053-t1950.*t1982)-Ld4.*Ma3.*t1855+Ma4.*t1845.*t2055+Ma5.*t1848.*t2052+Ma4.*t1848.*t2280+Ma6.*t1945.*t2310+Ma4.*t1845.*t1922.*t1908+Ma4.*t1848.*t1922.*t1954-Ma5.*t1852.*t1845.*t1986-Ma6.*t1852.*t1845.*t1986+Ma5.*t1845.*t1849.*t2050,-t1871.*t2240+t1867.*t2201+t1883.*t2208+t1986.*t2142+t1986.*t2146+t1866.*t2259+t1954.*t2290+t1908.*t2283-t1908.*t2276+t1948.*t2227+t1997.*t2215-t1903.*t2300-t1903.*t2305+t2050.*t2152-t2052.*t2144+t2055.*t2156-t2023.*t2294-t2280.*t2279+t2278.*t2310-t1867.*(t2242+t2244+t2246-t1862.*t2245-Ma4.*t1919.*t2193)+t2150.*(t2053-t1950.*t1982)+Ld5.*t1866.*t2140-Ld4.*t1855.*t2281,-t1871.*t2355+t1866.*t2371-t1883.*t2337+t1867.*t2381+t1903.*t2350+t1908.*t2363+t1986.*t2315-t1948.*t2345+t1908.*t2368+t1986.*t2319+t1997.*t2386+t2023.*t2341-t2050.*t2324+t2052.*t2317+t2055.*t2328-t2391.*t2377+t2376.*t2398-t2378.*t2400+t1903.*(t2356+t2357-t1948.*t2302-Ma6.*t1924.*t2310+Ma6.*t1925.*(t2053-t2329))+t1954.*(t2372+t2373+t2374+t2375+Ma4.*t1922.*(t1991-t2311))+t1867.*(t2351+t2352+t2353-Ma4.*t1923.*t2055+Ma4.*t1919.*(t1991-t2311))-Ld4.*t1855.*t2387+Ld5.*t1866.*t2313,t2377.*(t2422+t2423)+t1867.*t2431-t1871.*t2456+t1883.*t2444+t1866.*t2464-t1867.*t2459+t1903.*t2443-t1908.*t2435+t1903.*t2468+t1908.*t2463-t1954.*t2455-t1986.*t2405-t1986.*t2417-t1948.*t2448+t2052.*t2421-t2050.*t2409-t2055.*t2413+t2023.*t2439+t2376.*t2415-t2378.*t2418+t1997.*(t2450+t2451+t2449-Ma5.*t1927.*t2000-t1845.*t1849.*t2212)-Ld5.*t1866.*t2411,t2103-t1845.*t1974-t1848.*t1962+t1848.*t1965-t1950.*t1960+t1945.*t1968-Ma6.*t1860.*(t2077+t1982.*t2001)-Ma2.*t1871.*t2061-Ma2.*t1883.*t2080+Ma3.*t1867.*t2071-Ma3.*t1866.*t2069-Ma3.*t1867.*t2078-Ma4.*t1862.*t2065-Ma4.*t1866.*t2083-Ma5.*t1872.*t2000-Ma5.*t1862.*t2073-Ma4.*t1918.*t2086-Ma5.*t1873.*t2076-Ma6.*t1872.*t2000-Ma6.*t1853.*t2063+t1852.*t1845.*(t1975-Ma6.*t1853.*t1924)+t1845.*t1849.*t1970+t1852.*t1845.*t1977,t2130-t1848.*t2032-t1848.*t2035-t1950.*t2030+t1945.*t2059-t1845.*(t2060-t2043)-Ma2.*t1883.*t2061+Ma3.*t1866.*t2071-Ma3.*t1867.*t2066-Ma3.*t1866.*t2078+Ma3.*t1867.*t2069+Ma4.*t1867.*t2083-Ma4.*t1908.*t2065+Ma4.*t1954.*t2086+Ma5.*t1903.*t2000-Ma5.*t1908.*t2073+Ma5.*t1997.*t2076+Ma6.*t1903.*t2000-Ma6.*t1948.*t2063-Ma6.*t2023.*t2137+t1852.*t1845.*t2048+t1845.*t1849.*t2042-t1852.*t1845.*t2079,-t1848.*t2112-t1950.*t2124+t1945.*t2119-Ma4.*t1845.*t2086-Ma4.*t1848.*t2065-Ma5.*t1848.*t2073-Ma6.*t1945.*t2063-Ma6.*t1950.*t2137+t1852.*t1845.*t2121+t1852.*t1845.*t2116+t1845.*t1849.*t2127+Ma5.*t1852.*t1845.*t2000-Ma5.*t1845.*t1849.*t2076+Ma6.*t1852.*t1845.*t2000,-t1845.*t2290+t1848.*t2283-t1848.*t2276+t1871.*t2390-t1950.*t2294+t1945.*t2227+t1883.*t2393-t1866.*t2388+t1867.*t2396-t2000.*t2142-t2000.*t2146-t2083.*t2140-t2076.*t2152-t2086.*t2156-t2150.*t2137-t2063.*t2278+t2144.*(t2072-t2136)+t2279.*(t2064-t2135)-t1845.*t1849.*t2215-t1852.*t1845.*t2300-t1852.*t1845.*t2305-Cy3.*Ma3.*t1866.*t2071-Cy3.*Ma3.*t1867.*t2069,-t1871.*t2393+t1883.*t2390+t1848.*t2363+t1848.*t2368+t1866.*t2396+t1867.*t2388-t2000.*t2315-t2000.*t2319-t2083.*t2313-t2073.*t2317+t2076.*t2324-t2065.*t2391-t2086.*t2328+t2063.*t2398-t2137.*t2400-t1845.*(t2372+t2373+t2374+t2375-Ma4.*t1922.*t2377)+t1950.*(t2340+t2338+t2339-t2394+Ma6.*t1920.*t2376)-t1945.*(t2342+t2343+t2344-t2399+Ma6.*t1920.*t2378)+t1852.*t1845.*(t2356+t2357-t1948.*t2302+Ma6.*t1924.*t2376-Ma6.*t1925.*t2378)+t1852.*t1845.*t2350-t1845.*t1849.*t2386+Cy3.*Ma3.*t1867.*t2071-Cy3.*Ma3.*t1866.*t2069,I2_22+I3_22+t2196+t2205+t2254+t2237+t2477.*(t2110+t2111+Ma5.*t2477)+t2470.*(t2122+t2123+Ma6.*t2470)-t1848.*t2435+t1848.*t2463+t1950.*t2439+t2000.*t2405+t2000.*t2417+t2083.*t2411+t2071.*t2407+t2063.*t2415-t2069.*t2420+t2086.*t2413+t2076.*t2409+(t2422+t2423).*(t2064-t2135)+t1945.*(-t2445-t2446+t2475+t2476+Ma6.*t1920.*t2470)+t1845.*(t2452+t2453-t2480+t2454)+t1845.*t1849.*(-t2450-t2449+Ma5.*t1927.*t2000+Ma5.*t1921.*t2477+t1845.*t1849.*t2212)+t1852.*t1845.*(-t2482+t2465+t2466+t2467+Ma5.*t1926.*t2477)+t1852.*t1845.*(t2440+t2441+t2442-t2481+Ma6.*t1925.*t2470)-Ma3.*t2071.*t2078-Ma3.*t2066.*t2069],[6, 6]);