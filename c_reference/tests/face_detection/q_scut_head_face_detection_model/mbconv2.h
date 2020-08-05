// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#define L2_N 1
#define L2_H 30
#define L2_W 40
#define L2_CIN 32
#define L2_CTEMP 64
#define L2_HF 3
#define L2_WF 3
#define L2_COUT 32
#define L2_HOUT 30
#define L2_WOUT 40
#define L2_HPADL 1
#define L2_HPADR 1
#define L2_WPADL 1
#define L2_WPADR 1
#define L2_HSTRIDE 1
#define L2_WSTRIDE 1

// The convention followed for filter weights is F[groups][filter_height][filter_width][in_channels][out_channels]
static INT_T L2_F1[1 * 1 * 1 * L2_CIN * L2_CTEMP] = {-3750, 3738, 6290, -2041, -1623, 7761, 4317, 12857, 410, 6587, 5075, -7613, -3019, 4135, 11892, 7036, 9723, 1079, 2727, -1257, -3394, 6275, -6280, 2384, -8834, -1791, 525, 4983, 970, 6141, 1753, 719, 6645, 3383, -4612, -6029, 6228, -2799, 3486, 1114, 6796, 3155, 1998, 2553, 2207, 5860, 421, -1179, 335, 15541, 9347, -7082, -1529, -3032, 8159, 4429, 6851, -7796, 3055, -6766, -1366, 10836, -8690, 11744, 6836, -12678, 1600, -2403, 8567, -100, -1772, 16411, 3605, -1210, -1329, -2579, -4674, 2747, 12770, -7519, 6297, -4462, -8440, -2200, 13284, -432, 4802, -279, 3118, -5095, 6530, -3946, 4005, 5188, 4304, 2512, -1477, 3383, 6722, 3227, -1837, 4384, -1244, 6750, -14027, 11039, -14303, 165, -3609, 10334, 614, -1628, 2202, 411, 488, -3070, -861, 10303, 13543, 5848, -3630, 2464, 8762, 2203, 6814, -6878, -3642, 336, 1952, -7715, -7177, -3862, 3979, -499, 2284, -12339, -14060, -193, 1841, 5219, -6917, -4706, 6738, 1635, -8079, 672, 2712, 617, 4115, 20665, 4573, 373, 1951, -11404, 4280, 8592, 2758, 2084, 11536, -2321, -3811, 8742, 3270, 3578, 1901, -1191, 2946, 4927, -14080, 1208, 8032, -1320, 6948, -3155, -6722, 4627, -521, 15962, -3263, 3174, -4762, 10171, -3238, -1428, -8292, -2249, 584, -1671, -2546, -1211, 9857, -3247, 5497, -2331, 5896, -399, 4374, -3886, -9272, -4151, -7555, 7120, 2667, 175, -2244, 591, 1173, -8957, 5949, -5028, -8289, 580, 5214, 1723, 2554, -3026, 1702, -13253, -8468, 1671, -16072, -3075, -10339, 1483, 2967, -4929, -8959, 6996, 16730, -1416, 14760, -461, 6713, -2693, -4460, -684, 2776, -314, -3502, 216, -3881, 1373, -2807, 1707, -3789, 5968, 4102, -4730, 7303, 6627, -5088, -11914, -7410, 4537, -8928, 11494, 18087, -130, 7532, -1658, -2945, 8228, 5706, 19547, 940, 4696, 6609, 6565, 5457, 380, -1650, -301, -8608, -1084, -4239, 7342, 3331, 6380, -8109, 2651, 1339, 11348, 316, -5245, 7516, 3546, 858, 6516, 1755, 7640, 314, 2780, 5615, 2935, -11548, 6975, -3410, -6563, -6234, 6188, 2109, -1728, -1426, -360, 2446, -6453, 1834, 4442, -3386, 17447, -4045, -2893, 4667, 1723, 6246, 9027, 3189, -2630, -12900, 6649, 2121, -1471, 416, -452, -1260, -14379, 5291, -10818, -3606, 4208, -8446, 4761, 201, 4211, -6595, -13098, 4073, 8324, 3349, 691, 960, 6418, 85, 2601, 11621, -5263, 4148, 7161, 687, 12676, 10697, 9608, -360, 4480, 241, -11555, 4349, -11472, -2046, -741, -2047, -4222, -6028, -1896, -1932, 1942, -5416, 6991, -51, 2338, -7576, -5367, -4472, -2498, -11204, -6475, 3069, -521, 2572, -13207, -6734, -7668, -5063, 1473, 10573, 4798, 1520, 1526, -813, -4079, 7343, 2657, -7828, 1650, 1764, 6294, -8622, -2365, -2764, 13507, 12232, -2017, -5956, 10775, -2598, -2343, 1487, 5222, -1813, -3145, 1934, -2512, 22, 4522, 4888, 4176, 204, 3799, 236, -206, -544, 2888, 4529, -1917, -7524, 7245, 1124, 2636, -6399, 4697, -764, 7569, 632, 938, 7773, -10741, 8390, 8307, 1834, -9667, -4364, -2461, 141, 1663, 10935, -6165, -14, 1464, 2351, 199, -2625, -4088, 6879, 6106, -10891, -7797, 5913, -2494, -9427, 3366, 1145, 1481, 2809, 6607, 1698, 5416, -3358, 5872, 1690, -223, -564, 9115, 5699, -4779, 1998, -4478, -909, 1239, -9608, -587, 396, -5715, -5729, -9204, -1064, 2665, 3052, -2378, 7452, 166, 1681, 2390, 7695, 11836, 327, -3936, -7622, -1446, 2234, 84, -6948, 2278, 15476, 2084, -2213, -11418, 1301, 10788, -8698, 5297, 386, -7019, -3931, -2851, -2, -4448, 2426, 3945, -323, -17597, -3547, -5236, -3770, -1189, -10718, 4935, 9403, 1725, -5479, -3638, 13727, 2997, 7141, 1315, 497, 6690, -5512, -6819, 9102, 2742, 9044, -2195, 1642, 8134, 8809, -4119, -14858, 2653, -4053, -11565, 5513, 9080, -6514, -1838, 7939, 938, -3609, -5207, -4297, 3250, 3665, 314, 9992, 3606, -1678, -901, -13286, 7544, 8269, 8373, 1490, 2293, 12850, 1057, 3302, 4012, -2835, -3492, 10687, -933, -5369, -5145, 2014, 3365, -5571, -2904, -6918, 6138, 1217, 2213, -485, 1966, 2795, 60, 8939, -9366, 521, -9474, 2145, 5574, 2115, 11963, -3376, 842, 4241, 510, 3914, -18225, 3488, 11154, -5337, 2203, 2452, -2671, 11975, -691, 1132, -4114, -5929, 7857, 2694, -8816, -4195, 5821, 2304, -3892, -1834, 4401, -6553, 7827, -2209, -1980, -13726, -2735, -3648, 1279, -4675, 5261, -10721, -12746, 6278, -7687, -1283, -6414, 6907, 468, 4636, 10901, 12384, 11452, 3051, -205, 2469, 1881, 7787, -8755, 9514, -48, 4038, -7699, 2116, -1015, 1779, -1406, 6993, -12292, 3940, -7676, -920, -8284, -1067, 10886, 4899, -8054, -4727, 1298, -15320, -3060, 5063, 790, -5416, -2682, 16043, 4452, 2738, -8205, -2785, 10859, 1799, 2022, 1465, 1210, -294, 1938, 3454, 1930, -5745, 2833, 214, 9511, -8966, -3117, 1248, -2754, 3411, -1621, -945, 7757, -3285, -1462, 6298, -8183, -10519, 1057, 2986, 679, -3936, -2736, 3660, -834, 2587, -5649, -906, -4351, -12038, 277, 2236, -1979, 69, -419, -4049, 2782, 4049, -4305, -2487, 397, -2787, -133, -1151, 1267, -11773, 5656, -1686, -3402, -60, 1376, -11921, -1540, 2272, 2499, 390, -4459, 4057, 7614, -2141, -1067, 3263, -2328, 5040, 835, 4008, 2171, -2815, 6897, -10606, -561, -6977, -2883, -4773, 6389, 3226, -6058, -3176, -430, -2132, 2628, 4014, 2821, -7943, 7852, 1291, 374, 4213, -1507, 4566, -1076, -9624, 6871, -4387, -2202, 5881, 59, 510, 8900, -14781, 2449, -3664, 4019, -6780, 3387, -265, 10384, 2440, -5872, -4057, 7264, -4440, 7633, -157, -798, 7664, -1414, -2154, -1650, -1425, -4869, 3612, -4698, 13143, 1925, 6689, -268, 3794, -3268, 3590, -1710, 3632, -3264, 842, 5765, 5657, 8487, 2927, -3406, -811, 2320, 1930, -6797, 794, 19077, 536, -3309, 8194, -570, 7820, -4772, -8233, 2483, 1974, -569, -4586, 3132, -608, 8019, -1158, -3780, 2789, 1726, -6784, -1830, -1508, 6446, 9936, 472, -854, 4748, 5197, 1186, 2676, -15164, 2232, -5388, -12058, -5348, -8613, -465, -721, -3834, 1895, 21, -4458, -1182, -6079, 1885, 376, -1131, -3375, -1306, 10279, -3803, -1987, 2682, -5035, 2279, 1871, 2945, 1841, -6417, -131, -9877, -1093, -11793, 1122, -7855, -6555, 119, 4366, 2215, -13039, 5838, 2350, -12855, -4035, -5201, 3928, -11175, 9525, -6009, 1410, -9838, -8038, 11548, 7057, 6176, -7989, -3504, 2692, 3265, 8093, -7610, -2939, -3323, 21171, -8492, 457, 8162, 2900, 9584, -6019, 5051, -11018, -11574, -3794, 765, 7358, 8389, -2790, 1396, 3144, 10545, 8890, -436, -8754, -14425, 7540, 4355, 1105, -13964, -1865, -1546, 2202, 5176, 284, 2080, -2835, 324, -5472, -1909, 1215, -6896, 7217, 1162, 15276, 691, 627, 5551, -1164, 8190, 1057, 4315, 1708, 6471, 5893, 10376, 4600, 5110, -2004, 5307, -5958, -3165, -2207, -10318, 8819, 2054, 5302, 13733, -827, 6569, 3076, -7919, 8828, 1887, 4676, 935, 3791, -3972, 3699, -2780, -2500, -7319, 7901, -1969, -1754, 14088, 13181, -1713, 7636, 5227, -4096, -3226, -2110, -209, -622, 1366, 2270, -278, 4128, -13286, -1106, -5254, 5045, -1587, -10729, -1167, 334, 4242, 1207, 6370, 2146, -2240, 2645, 6959, 2412, 6506, -4281, 7384, -4882, 908, -5218, 2739, -493, -7003, 3724, 6301, 4495, 1986, 3575, -13143, 2042, 7458, -4690, 10022, -7316, 1441, 1838, 5881, -6613, 1324, -12083, 805, -58, 4368, -9329, 6330, 5529, -2291, -993, 11548, -4314, -919, -1458, -4535, 3626, -1317, 53, -2717, -11039, -3102, 9503, 1949, -1700, -1138, -1044, 3400, -4047, 2499, 273, 3794, -12372, -1417, 7705, -5301, -2349, -1312, -1202, -4705, 614, -6823, 1999, -2123, 4188, 2134, 1422, -1561, -7188, 6079, -8047, -5989, 4831, 4490, -4491, -6223, 2121, -11953, -1772, 13347, -2955, -4012, 14798, 784, 453, 2670, -4053, -2833, 3485, 877, 6162, 340, -1291, 4951, -7896, 4851, 788, 126, 2059, 679, -2875, -8303, 8974, -3605, 1102, 10310, 3413, -556, 8426, 3615, -281, 3104, 2423, 5741, -584, -1791, -1668, 2321, -4051, 8055, 1464, 7251, 5351, -4355, 1201, -11461, -1723, -4346, -8303, 7428, 2613, -7552, -7190, -2981, 985, -5388, 4312, -6430, -9149, -2301, 4079, -9077, 1769, -2057, -4009, 3414, -741, 899, 10829, 479, 4119, 5275, 2176, 607, 3823, -40, 1967, -4129, 3999, 4243, 12926, -4205, 8899, 224, -4062, -7790, -2561, 9823, -7816, 2725, 5567, -2955, 2639, -403, -2591, -2348, 1351, 4261, -8642, 3474, 13398, 23312, 4235, 1634, -10733, 967, -1250, -3625, -3648, -3039, -1023, -2212, 7397, -9834, 6465, -9773, -4326, 11467, -690, -6618, 768, 17363, 8629, 395, 5496, 790, 4975, -1795, 12065, 12745, -1539, 2747, -10328, 16498, -3109, 11735, -124, -2486, 7094, -710, 6716, 4055, 6749, 8844, 346, 1271, -1563, -5745, -1012, 8574, 8809, -4481, -4273, 177, 7873, 5731, -438, 3187, 11560, -4105, 1625, -1957, -8182, 4416, 1866, 441, 3489, -1652, -2566, 1067, 2095, -8493, -995, 2164, 1845, 1423, 4332, -4608, -8569, -4251, 7503, 4410, -9774, -2846, 5604, -3566, 6543, 8720, 2739, 4191, -13278, -866, 7680, 5304, 7819, 3570, -2114, 623, -1462, 830, -4955, 2666, -425, 1375, -6329, 2269, -4838, -6849, -2811, -156, 681, 4505, 1606, 544, -2351, -3670, 2928, 7827, -8414, 273, 1269, 10739, 9275, 2160, -707, -2849, -12288, 1715, 5313, 2427, -9968, 5738, -3571, -10051, 295, 705, -11569, -2323, -8441, -4242, 4896, 4936, -1525, 6, 1201, 2013, -4950, -9583, -2699, -9047, -1372, -434, -12239, -4001, -467, 3781, -5852, -558, -1443, -4847, -4893, -2182, -743, -2637, 2974, -3649, 5210, 3997, 633, 3265, 6225, -8707, 4965, -3779, 12001, -513, -2312, -7915, 2007, -2611, 7318, -449, 4913, -3051, 6226, 1869, 297, 2599, -1707, 12669, 4806, 5980, -3960, 2460, -3751, 2854, 11026, -6148, 11403, -2336, 1292, -8780, -2037, -1494, 4728, -8101, -2070, 83, 10654, -1676, -1275, 5967, -2449, 4011, 2041, 1433, 2780, 242, 6157, -640, -7731, -3032, 9302, -1295, 6644, -6144, -1145, 8873, -2490, -9819, -6383, -177, -1372, -991, -710, 7954, 6812, -1348, 9407, -2865, 753, 1947, 2602, -4012, -3795, 5339, 1634, 9633, -6036, 2218, -5720, -1895, 7581, 15033, -4367, 869, -8960, -12563, -8598, -2610, -7487, 4691, -4699, -97, -1029, -3073, -1987, 1502, -8035, -3016, -909, -22372, 2286, -5742, -3260, 224, 12337, 8226, 2838, 5914, 3388, -1892, -3959, 7845, -5950, -1667, -1639, -1054, 3433, 1940, -1900, -6761, 3932, -648, -716, 688, 2265, 5486, 4388, 9733, 8007, -1915, 2330, -9750, 9853, 5153, 2868, -127, -13588, -1730, 4872, -3721, -2028, 3292, -3800, 15620, -1678, -27, 7113, -5517, 4788, -4114, 484, -4089, -6222, 9095, 1666, -464, -1459, -4614, -935, 18393, 27, -144, -2033, 23613, -5609, -10945, -354, -1969, -3197, -11655, -8751, 6758, -9445, 7977, -2507, 4938, -2001, -791, 1264, 2816, -4077, -4671, 4508, 1609, 1190, -6346, -7089, 1197, 5879, 2873, 5932, 10571, -55, 452, 6482, 6778, 209, 7229, 4250, 4613, 4580, 4240, 2016, -5480, -627, -5494, -3138, -43, -1097, 2277, 4918, -220, 12680, 5397, -5923, 25, -10364, -4109, 6380, 6210, 3021, -2969, -5175, -610, 614, -2374, 13651, -3320, -3140, -4870, -5674, -3662, -1316, -9230, -3812, 5458, 1031, -7644, -17109, -6084, 4794, 3707, 2989, -1740, -4631, -719, 745, -937, 501, -200, 475, 4559, 185, -7923, -3908, -8690, -514, 2735, 70, 7012, -8932, -14800, 7780, -6487, -666, -1576, -4725, 1665, 4629, 19033, -7600, -6688, -3125, 11401, 8196, 7766, 561, -5152, -3250, -3902, 4563, 1619, -10783, 6870, 4105, 20837, 5331, 12341, -2831, 3671, 2831, 3936, 6233, -6111, 4790, 6685, -2377, -1597, 9959, -6020, 15964, 2834, 1813, -4141, -4438, 2527, 4279, 662, 2094, 2690, 5279, 2911, -2032, 7328, -6506, 3909, 859, -2384, -8011, 13774, 15288, -725, 5882, 7388, 1023, -10471, -1074, 3480, 331, 3056, -485, -528, 3184, -5303, 4137, -2712, -10197, -5274, -3798, 3879, -5390, 2898, -7620, 227, 15522, 8898, 1295, -3703, -1885, 5071, 679, 967, -2278, 14438, -95, 1817, 6108, 4141, -5312, -3574, 1710, 2036, -1012, 10598, -9286, -2749, 5595, -5697, 7923, 1408, -11385, -1351, -3075, 6618, -7150, 5436, 251, -10841, 15558, 9719, -15617, 3376, -549, 10697, 10729, -162, -3181, 3516, 1011, 8051, 3121, -13654, 1561, 257, 5291, -3941, -1241, 9491, 3818, 2551, 1392, 3643, -871, -6858, -10192, 11412, -730, 454, 2310, -7939, 8993, 208, 6539, 4553, -8827, -2553, -4774, -12238, -662, -25, 3166, 3369, -2347, 9331, 313, -11366, 3295, -1459, -333, -704, 449, 2741, -3596, 2828, -4739, -5316, -6329, 507, 6568, -290, -915, 3944, -2485, 12494, 11042, -10676, -1495, -3008, 4807, -3838, -2958, 10832, 661, 2912, -560, 6913, 4726, -8455, -9213, -1501, -4161, -7843, -4630, 2435, 11649, -6382, 5987, -8010, 2752, -6049, 4667, -4462, 484, -5214, 10785, 5069, 10784, -4100, -7083, -10784, 5823, 5339, -9717, -8382, -8613, -3579, 6723, -1002, 14924, -1823, -8863, 1311, -5963, -2835, 14236, -1276, -2186, -7704, -2004, -1091, 5106, -1302, -14987, -2531, 45, 6620, -2829, -7055, -4358, 437, -3234, -319, 12489, 6807, 2017, -7725, -4636, 4263, -6485, -718, -5645, 2601, -11199, 3851, 2706, -2663, 7458, 525, -5704, 11802, 10501, -6390, 12163, -1629, -729, -3196, 10272, 10767, -11926, -2299, 708, -192, 5142, -4885, -5997, -2971, -1602, -15767, 3797, -582, 5990, 6388, -7488, -6714, 2574, 4750, 1375, -11661, 1459, 3659, 2671, 945, 4116, -1884, 1153, 347, -2398, -1937, -635, -3301, 2375, -4463, -712, 848, 5535, 2948, 18845, -2288, 1249, 28, 6516, 1973, 1171, -1314, 5468, -3276, -1411, -38, 1820, 6137, -3386, -5171, 2707, 10818, -6215, -3868, 4479, 5132, -2748, 3200, 719, -5003, -3654, 1788, -2372, -2555, 6733, 4789, 10215, 5858, -1880, 2296, -711, 4570, 1236, 177, -670, 379, -35, -1748, 1514, -321, 4458, 294, 10956, -5682, -4525, -6098, -1292, 4244, 12535, 25, 3645, -4457, 5168, 4450, 4598, 2594, 5499, 6295, 2449, -9206, -464, 5145, -4207, 4243, 6451, 4600, -13273, -5146};
static INT_T L2_F2[L2_CTEMP * L2_HF * L2_WF * 1 * 1] = {2080, -7885, 2899, 4494, -8000, 2750, 4423, 18388, 2230, -7157, -1749, -4331, -10373, 4418, 956, -1206, -6795, -4242, -4082, -3755, -5082, -5034, -9723, -2418, -3172, -2779, -39, -7049, -3862, -4635, -8798, -6613, -4640, 2160, -5442, 3228, -9960, -5323, -5986, 1685, 13515, 81, -5039, -2929, -6178, -1431, 3636, 278, 12131, -4842, 851, 4962, -5051, -7977, 7052, 1697, 4576, 4904, 3534, 2478, 7720, 4329, 6851, 10763, 6335, 9375, 2378, 6912, 2714, 7749, 2052, 4643, 5601, 13178, 3721, 6077, 2400, 5887, 4026, -1523, -1389, -4378, -1854, -2559, 8000, -9462, -2264, 17303, -3455, -4549, 1379, 3354, 1853, 4717, -2113, 16807, 2268, 2309, -5653, 8960, 19920, 3869, -4605, 871, -2396, -1073, -3138, 4304, 2196, 2340, 901, 2822, 13974, 5815, 2213, -5620, 631, -2556, -4810, 4463, -4302, -16176, -2317, 1188, 5407, -996, 2086, 3426, 8274, -688, -8254, 13610, 7843, -2665, 16478, -3189, 19767, 4134, 243, 1389, 2685, 138, 3188, -338, 1808, 10499, 1013, 1443, 14746, 901, 616, -1441, -2495, -8295, -6184, -6016, -4342, -3788, -2001, -5048, 5604, 833, 5882, 17251, 5925, 3714, -6009, -4456, -6231, 1378, -1464, 21358, 1719, 1837, -1380, -2518, 2365, 22, 273, 1382, 3741, -12601, 8601, 2029, 14400, 364, 117, 131, -1166, -4967, -4730, -4606, -5870, -6099, -6186, -516, -2015, -1250, -7539, -8605, 884, -5159, -3690, 873, -4474, -6691, -3418, 2365, 6438, -4049, 8207, -226, -8055, -14, 10489, 8857, -6081, -9133, -1354, 1495, 19646, -5340, -3809, -2660, -2465, 5021, 4991, 5745, 5737, 4871, 5962, 7029, 8911, 4997, 6873, 2116, 5502, 8840, 5733, 7811, -16477, -15994, -11079, 5831, 761, -10578, 7533, -4722, -8153, 4629, -2926, -10214, -9295, -4262, -7575, -2325, -1985, -5131, -4131, 1817, -3902, -14118, 17403, 2510, -10059, 3626, 1255, -148, 2045, 1943, -6935, -11092, -3455, -7640, -5740, -5125, 2350, -1240, 467, 6056, 3119, 5056, 5094, 8638, 898, 8749, 8485, 8513, -4672, 10124, -3642, 15319, 2603, -977, 8729, -6062, 96, 933, 19776, 4237, 136, -3150, 2332, 2213, -320, 334, 3919, 2459, -3883, 17340, 2295, -863, 3491, -676, 3597, 232, 89, -325, -1992, 12991, 8437, 4326, 1006, 2656, 4340, 1696, 5987, 7552, -13126, 3486, 12100, 7122, 7596, -5961, -5203, -3372, -7646, 9579, -8163, -4508, -6478, -3166, -1185, -6824, 842, 4992, 2395, -27, 6866, 16528, 6050, 6449, 13348, 6897, -8558, -10377, -3049, -8806, -6868, -6204, 887, 5594, -1165, 3785, -360, 7074, 1166, 12998, 7349, 14192, -515, 379, -11925, 9112, 546, 5180, 3493, -3256, 553, 4489, 4599, 12190, 1652, -78, 11188, 3695, 2450, -7384, -2419, -7404, -8487, 4846, -12062, 2722, 5240, 9844, 2323, 6730, 563, 3178, 13831, -4260, 3999, -10516, 3640, 7624, 4638, 837, 13805, -9107, -1353, -5119, -7103, -1678, -796, -5230, 4380, 7786, 4382, 3221, 858, 803, 8106, -1773, 3659, -2922, -6545, 25193, -154, -6073, -3666, -5779, -4734, -6145, -2973, -3205, -5081, 12326, -5890, -4872, -3553, 11621, 15382, 5533, -5753, -5550, 1620, 1816, 1427, -2855, 1923, 270, -326, -4387, 18720, -3821, 4004, -2960, 556, -5909, -2450, -1506, -399, 12370, 7570, 7649, -3329, -3070, 11296, 9003, 6728, -180, 6234, -5933, 175, 2071, -9723, 10172, 992, 13325, 17177, -8491, 12119, -3129, -7804, -3219, 3302, -3639, 1659, 8187, -1695, 6063, 12716, 2804, 14519, -6992, -6215, -165, -6632, 14091, 244, -6695, -1446, -2590, 2008, -3421, 3648, 5438, 6704, 6948, 5377, -15007, 3760, 2988, -2489, 2559, 103, -3002, 3127, 5102, 19374, 2955, -2872, 6107, -1751, -4563, -2661, -8604, -4356, -7638, -5544, 6728, 6487, 1126, -1456, 2088, 3290, 6285, 14121, 203, -507, -2010, 396, -761, -6525, -738, 1151, 17126, -578, 5154, 802, 3433, 7082, 1105, -1007, 9645, 3667, 9861, 4065, 11571, 3118, 11320, 6566, 1247, 1154, 4755, -372, -1985, 33, -639, 16383, 3047, 844, -2666, -392, 794};
static INT_T L2_F3[1 * 1 * 1 * L2_CTEMP * L2_COUT] = {2729, 1241, 1633, -10062, 9746, -5698, 2789, -8492, -2746, 3065, -897, 6067, -5556, 1229, -3359, 5544, 83, -248, 6836, 13697, 1133, 5335, -5907, -804, -4383, 4828, -13668, -4884, 3286, -3878, 3110, -1235, -3396, 3367, 468, 2794, -906, 596, 1831, -4652, 2066, -504, 504, 2345, -5044, -2432, 6107, 7470, 5720, 3746, -10405, -3196, -4639, 490, 11839, -7313, 712, 4038, -1364, 3210, 4344, -8718, -6497, 7310, -8993, -9868, -5058, -347, -12051, 6553, -1155, -6801, -11029, -13088, -6544, 3406, -4042, -5169, 3842, 1584, -6115, 3729, 5274, -9235, 2069, 1370, 2075, 2558, -3535, 3855, -1952, -15037, -831, -1086, -2820, -1530, 4939, 2826, 2578, -11202, -1944, -1242, 5847, 1959, -1328, 3520, 9148, 6048, -2252, 5792, 2607, -4020, -628, 3139, -355, -9914, 5596, -8360, -357, 5, -13624, 7632, 379, -4423, -204, -10914, -2131, 1885, 3509, -11065, -5871, 1901, 6854, 4766, 591, -1976, -1532, 7821, -464, 5884, 5336, 4939, 1067, 2242, -473, 1591, 2494, -4113, -11551, -895, 2300, 7354, 9281, 7418, -1521, 2501, 3168, 3564, 94, -431, 2697, 1867, -719, -2526, -2233, 8815, -1532, 3792, -876, 3489, 3021, 4819, 584, 3435, -2191, -5487, -3661, 2280, -5028, 2865, 1608, 6930, 3600, 150, 1000, -2554, -2763, -220, -4968, 4933, -2305, 2149, -8026, 3846, -4744, 1155, -3490, -849, -5517, -10687, 5650, 1368, 4319, 9632, 4701, -2747, 5638, -7999, -5318, 3570, -2347, -5857, -5140, -1983, -3617, -672, 1474, 4889, 5149, -11196, -2349, -99, -6620, -912, 1996, 9863, -3030, 3355, -4173, -11963, -8710, -3913, -1666, 5236, 5171, 4391, -10167, -1559, 5809, -3443, -1799, 5473, 8184, -9114, 5576, -5827, 1987, 81, 218, -929, -949, -5221, -2189, -5967, -5396, -4987, -17234, 5725, 5095, 9249, -5567, 1387, 2776, -4935, -3953, -6487, 639, 4218, -1374, -3934, 11594, -5632, -6880, -73, -13564, -2987, 4157, 9793, -8499, 979, 4321, -4374, 1239, 5312, 957, 4063, 4394, 2525, 3542, -783, 4380, -1295, 5748, -2918, -398, -927, -3363, 7620, -2695, -6668, -5328, 2758, 514, 4901, 957, -885, 2352, 877, -3231, 987, 1889, -2940, -5785, 3994, -2447, -542, 3923, -5368, -1265, -3868, -4433, -4795, -6355, 974, -2333, 5101, -2897, 2088, -1712, -9542, -5655, 1726, 4347, 1428, -2068, 2405, -4136, -8463, 4650, 3843, -1230, 6258, 2412, -3299, 11291, -3583, 3754, 1501, 4610, 2505, 5649, 9227, -5700, 10875, 3910, -2777, 8375, 2796, 6827, -8273, -737, -11240, 5722, -4279, -4497, -1118, 6520, -10211, -4899, 1345, -6477, 2517, 1508, 1045, -1857, 112, -3970, -10603, -9837, -177, -4047, -2334, -12352, 4683, -3521, 4748, 6968, -1767, -6069, -8051, -1612, -6610, 8882, 2171, -414, -1430, -1520, 2458, 5825, -6946, -2428, 759, -7706, -514, 6461, -7672, 1712, 5636, 1921, -4266, 2881, 8357, 287, -2768, 1333, -8846, 5889, -11123, 1777, -1432, -4854, 1739, -1621, 3059, -3056, -5626, -2114, -8311, -6257, 3659, -4552, -5804, 7108, -2836, -2037, 2243, -31, 2458, 8754, 498, 3112, -2649, -4596, -7527, 1607, 868, 1238, -8765, -1645, 14146, -3621, 71, -8686, 199, -6493, -2441, -1126, -4302, -409, -4250, -4395, -2906, 5563, -5635, 3257, -3919, -9673, -21001, -5560, -2314, 10356, -12491, -10269, 1826, 9193, 9880, -7999, 1482, -5054, -4353, 2979, -1763, -829, -6578, -6568, -1089, 3315, -1745, 6832, -4152, -471, -1097, -2022, 1517, -10532, 7016, 1157, 3331, 5423, -10949, -9640, -1943, 5136, -3590, 5918, 8407, 3976, -4810, 6307, -1842, 6733, -2609, -7633, 3098, 8450, -4291, 2814, 1641, 2855, -7605, 1158, -1828, -7882, 3183, 6543, 5264, 3632, 1980, -10332, 660, -4008, -67, -791, -3239, -16414, 1311, 570, 1318, 3283, 2299, -5936, 2096, 16378, 4502, 263, 1290, -1646, 5825, -3283, 1281, -9642, 3157, -1095, -2244, -5339, 4801, -1498, -2544, -1623, 3037, 2247, 4582, 514, 287, -270, -2406, 10900, -1197, 3362, -9344, 4058, -2021, -5028, 9140, -2270, 510, 7892, 5993, 4946, -4483, 2682, -4345, 2065, 634, 6115, 2055, 3992, 8426, -9994, 1929, 6927, 3255, 2555, 493, 298, -6563, 655, -4745, 2465, 5914, -1740, -1304, 2422, 11357, -2162, -8263, -15566, 190, -1718, -2061, 2730, -10827, -4673, 2326, 1991, 1039, -505, 5677, 1310, 5167, -1054, 5574, -10362, 3302, -1179, 288, 7224, -2815, -8988, 4624, 2464, -11268, -865, 9953, 2010, -1785, 2712, 5803, -230, -3756, -826, 5280, 1872, -1772, 5980, 13985, -716, 7535, 9640, 4402, 6831, 10267, -647, 9368, -2037, -5890, -6729, 1836, 5820, -5888, -3797, 839, -15448, -373, 9953, 3973, -1519, 459, 4513, 4646, -8676, 7166, 4731, 9166, 4203, -408, -1248, -873, -463, 3096, -776, 770, 631, -410, -9772, -6113, 6819, 2201, -4924, 4957, 2378, -4418, 2366, -10148, 2208, 1007, -12802, 1684, 7131, -10086, -4248, 1689, -7636, -2218, -11664, 2275, 366, 5487, -590, -4591, -4323, -4069, -2518, 221, -2450, 6941, 1370, -651, -467, -5594, -7943, 5646, 7301, 5422, -8612, -4522, 535, 6100, 5282, 161, 1646, -497, -2928, 4159, 5573, 2344, -4128, 3397, -949, -8412, 5409, 2056, -1874, -7942, -730, -133, 7139, -2511, -193, -3286, -2069, -4184, -785, 4973, -2131, -1311, -3614, 2461, -3784, 6170, 1042, 699, -7313, -10204, -4372, 2028, 5736, 9845, 4298, -6525, 5394, 3618, -4041, -7644, -2615, -1398, -1949, 7463, 840, 4307, -1803, 385, 1126, 4450, -326, -294, 5725, 1446, -2065, 2598, 6298, -7508, 6192, 779, -5505, -768, -2343, -2992, -2352, -2757, 5210, 5836, 7757, -3563, -4646, 947, -4616, -4032, 1371, 5540, -683, -7690, -2775, 5103, 3893, 6074, -969, 780, -7206, -6027, -568, -9383, 6471, -3625, -5331, -2567, 5935, -5873, -1937, -7924, -5058, -283, 5464, 11060, 4224, -2644, 3867, -16656, -255, -3078, 2171, -372, 2531, -1088, -3158, 4849, 4669, 1535, -1641, 3600, 6897, -9019, 250, -9455, 6881, 3534, -8826, -4846, -428, -4222, -2227, 1212, -3838, 6543, -689, 5412, -6500, 1740, -5067, -6353, 188, -735, -167, 3958, 2737, 0, 2928, 959, -2662, -4998, 1716, -908, -5773, -2970, 5767, -2043, 295, -2692, -9350, 13932, 1609, -8154, 3014, -2342, -6686, 1444, 2203, 5634, 7436, 1952, -9891, 6085, -10025, -5065, -5450, 2103, -6651, -3842, -2786, -1357, 2674, 1967, 2030, 4908, 1268, -5409, -7740, -3330, 4141, 6903, 4234, -3241, 5115, 6590, -10752, -4564, 2363, 1592, 1767, -13075, -1199, -6815, 3805, 250, -1135, 635, -1180, -1211, 2111, -6956, 3194, -545, 11154, -1128, 4492, 4630, 1106, -9345, -4352, 5923, 3535, -3337, 111, 6310, -5812, -7310, 2932, -10344, -1722, -5016, 847, 586, -3515, 1297, -6785, -7125, -6392, -4431, -3822, -1127, 232, -6498, -9696, -8141, 10186, 1297, -4872, 5000, -6240, -2050, -3342, -9087, 6643, 1594, -8848, -1082, 3905, -3866, -2907, -3175, -8252, -5486, -3452, 740, -12706, -7173, -2527, 58, 5069, 6276, -1734, -19, 7213, -672, 9566, 9121, -6806, -3444, 2007, -4767, 3636, -7004, 2665, 10372, 1580, -3018, 8192, 8119, -10242, 8344, 16861, 4902, -2312, 1819, -8651, 673, -1583, -4592, 3863, -15125, 8657, -931, -603, 1471, -14193, -4443, -2198, 8992, 1013, 155, -7021, 4235, 8838, -4524, -7575, -1293, -2383, 5895, 2734, 8191, -2470, 1254, 6952, 14347, 5676, -4998, -7328, -3707, 1307, -13286, 511, -7977, -5494, 1791, -3668, 6127, 2646, 3231, 8998, 3769, -1039, 2649, 129, -596, 305, -412, -6096, -1385, 5832, -4333, 91, 998, -142, -3087, -1439, 6697, 6593, -4576, -8981, -942, 3187, 2397, -749, -2654, 5564, 3291, 6425, -4788, -2789, 2929, 1587, 3243, 5093, 2985, -809, 1014, -2882, 3040, 558, -2058, -2910, -6301, -4578, 1161, -923, -12663, -5533, -5075, -113, -5036, -8298, 244, -5099, 2126, -5166, 3643, 1818, -5823, 4325, 4482, 4374, 9222, -4963, -5472, 4283, -7778, 923, 2290, -472, -3480, 139, 4130, -3628, 2610, -6832, 3876, -6020, -1126, 3543, 10383, -497, -458, 5519, 2045, 2193, -255, -7028, -1874, -1793, -7389, -8063, -13017, -9591, -3596, 13267, -252, 4114, -1159, 5447, -9865, -4174, 6623, -5075, -2166, 1143, 6013, 8896, -11996, 2750, 6906, -5211, 3010, -6612, 11128, 8324, 578, 984, -12440, 4345, -4502, 379, -7567, 15539, 4144, 850, 3843, -587, -5623, 810, 2494, 8027, 4876, 524, -2684, 6484, -5450, 2316, -3478, -16424, 3630, 571, -9582, -5552, -5842, -4785, -4796, -37, 139, -1997, 8494, 793, 4224, 1416, 9689, -7026, -8348, 59, 2042, 5437, -12626, -1082, -2206, 3983, -2450, 2799, -4470, -596, 6643, -7127, 3788, 12209, -1999, 2441, -6221, 245, 13529, -2996, 1446, -8361, 8387, -2242, 746, -1669, 4802, -2164, -14118, -441, 9700, 12471, -46, -1509, 3823, 7058, -2058, -2373, 2390, 4845, -3862, -2996, -6487, -7838, -1927, -11525, 98, 1511, -6969, -2689, -257, 1063, 5776, -8912, 2014, -425, -1126, -817, 9436, -4552, -1900, 5637, -7423, -1352, 1080, 4643, -2633, -4128, -7500, 1437, 557, -2331, -904, -4886, -341, -3705, 5854, 5862, 3057, -951, 4120, 1852, 8945, 3798, -1320, -2765, -2248, -1830, -7188, -8240, -2103, -4026, 4297, -828, -2208, -2614, -121, 3965, 7354, 1701, 2293, -2133, -1159, 3403, 858, -8253, 5840, 251, 73, 8991, 1752, 5450, -1690, 3956, 7626, 4744, 1721, 168, -3148, 3443, -4052, 506, -2303, -3581, -5336, 6183, -3015, 3155, 1772, 3285, 1034, -3371, 1724, 6309, -4805, -3611, -3583, 2331, -2076, -2437, -13085, -9957, -690, -2491, -7732, 12026, -9541, -6624, 5046, 1980, -5868, 1037, -6036, 9112, -6353, -1210, 3820, -1221, 1987, -237, 1479, -2905, 3812, 1532, 5525, -376, 496, 569, 2102, 1280, 3514, 6193, 1848, 5167, -11404, -10494, 4160, -5064, 453, 1670, 1259, -5615, -1085, 1835, 1198, -3004, 5828, -2157, -3979, -1192, 3013, -3306, -3620, 3634, -3900, -3767, 389, -5809, -8928, 3571, 6717, -4888, 6771, 1404, 1671, 8030, -4131, -4765, -3492, 5217, -2720, 6720, 1605, -3441, -5160, -1447, -5051, -919, -4632, 5550, -2965, -652, -3503, -3847, -2484, -348, -2791, 4998, 6270, -1468, 396, 2770, 3070, -3607, 4009, -3415, -11156, 3458, 2853, 1780, -466, -1163, -6793, 5677, -4715, -1848, -7391, -11729, 6217, 5485, -1295, -9328, 3298, -4959, -3152, -7121, -5748, -2473, -9727, -10380, 10171, -8148, 14598, 16366, -18048, 4741, -9581, -3217, 2776, -6609, -11192, -6269, 4530, -2387, -4626, -921, -2740, 1139, -575, -4388, 4425, -7304, -2022, -7693, 2202, -5953, -1845, -9512, -1169, -4036, 309, 4659, 855, -2398, -50, -3330, -4108, -5914, 9985, 1319, 572, 7165, -1416, 1009, 5994, -2527, -5904, 72, 4284, -5048, -3050, 10692, -2837, -312, 482, 9710, -528, 3278, 173, 2680, -761, 4532, 11240, -6791, -1716, 6004, -1264, 3399, -653, -1156, -7217, -760, -1245, -615, -2426, 11072, -5199, -7756, -1377, -428, -3192, 1845, 5994, 8085, 2989, 2373, -3215, -9340, 5487, 3327, 206, -3638, 5850, 3295, -697, -1084, -2436, 5371, 4357, 5158, -4769, -12001, 4408, -4759, 4415, 13184, -632, 3320, 6120, 5810, 3929, -2439, -5210, -520, -10124, -6649, -1161, 2246, 4831, -1280, -2511, 7745, -4539, -2148, 104, 2176, -2957, 259, 2889, -144, -361, 4308, 3628, 157, 8583, -2199, 2331, 1735, -2380, -6281, -8213, 3574, -3841, 6476, 8269, 4454, 533, -2823, -899, -2230, -786, -5639, -2349, -2348, 4161, 614, -1236, 5690, 4806, -2522, -1365, 4408, 537, -3779, -1262, 1100, -279, 2315, 6013, 1560, -2274, -1169, 6583, 1731, 1459, -852, -9876, 5126, -10124, -5240, -5539, -3530, 1054, -8960, 7060, -8383, 13076, 2203, 4021, 927, -4771, -13667, 12024, -5761, 15334, 9871, 2803, -1708, -1866, 16546, 1438, -16683, -9015, -3327, -10427, -6387, 2499, 5970, -7269, -7540, -56, -1315, 8549, 604, -2389, 8384, 9082, -3857, -6597, -1407, -4385, 11125, -4149, 4891, 2039, 6786, 4532, -561, 6369, -6561, -1425, -11772, -1521, 5310, -5783, 4218, 209, 307, 14586, 9213, 9083, -3153, 12108, 6028, -4473, -109, 3825, -1680, -4476, 4472, -1337, -7160, 1359, -4628, -5260, 17569, 683, -2998, 1956, 5654, -2073, -4605, -5923, 6187, 12031, -14324, -6314, 1839, -6317, -10351, 4587, -354, 2061, -3665, -7915, -381, 1017, 2558, 2303, 1124, -1316, -4358, 591, 2831, 3485, -4074, -3595, 2594, 835, 1729, -4842, -863, -3350, -936, 5749, 654, -8418, 5100, 4444, 951, -641, 711, -969, 7862, 1595, -4598, -2089, -10435, 5096, 117, 6138, 1265, 4361, -4425, 434, 35, -4398, 4470, -1003, -2239, -3788, -6032, 499, 2726, 1459, -1957, 9517, 1793, 1416, 8231, -3365, 1009, 399, 4099, 5247, 9063, 4887, -8056, -7571, 1321, -3796, -2287, -395, 5432, -9033, -1156, 7882, -3889, 4147, 2104, -1587, -801, -5754, -6491, 2826, 5109, -9845, 1861, 6844, 7623, 3327, -2938, 4970, 3604, 8921, 8393, 683, -933, 525, -5494, -2027, -1175, 6992, -4422, 9832, 2975, 324, 3774, 10589, -4525, -2785, 571, 4321, -3281, -2178, -152, 2993, -1671, -5009, 5322, -15506, -4061, 1701, -1995, 5968, 7297, 3963, -1629, -2548, -3616, 926, 1193, 1529, -4232, 2420, -1563, 1811, -1913, 4840, -6930, 5370, 8376, -4707, -2176, 3523, -6339, -4167, 3332, -7220, -5733, 4032, -6120, 3561, -1798, 469, 3030, 2047, -3078, -7895, -437, 4785, 8515, 1416, -6516, -4711, -1370, 2005, 3450, -8104, -2000, 7051, 2110, 365, 3375, 6968, 3715, -3147, 5434, -5223, -8255, 1204, -3760, 501, -4971, 456, 6862, -4286, 3241, 258, 3374, -300, 3360, -1987, 3346, -3800, -4309, -350, -205, -4215, -523, 5515, -1769, -1276, -5683, -996, 8898, -2312, 8000, 5945, -3366, -95, 5285, -6195, 2318, 922, -11902, 7663, -3341, -2971, 8794, -1426, 1628, 5159, 5302, 976, -2207, 2935, -541, 12150, -1662, 9929, 1610, -5305, -5505, -8560, -4589, -14174, -8915, -1322, 9182, -5462, 3514, -2510, 6182, 160, -6380, 4422, 2124, 929, -1516, 6682, 1215, -12713, 1906, 3086, -2074, 4938, -6172, -2277, -5633, -4441, -4391, -10166, 2688, -2798, -4954, 804, 235, -9387, 1473, -168, -3500, 2712, -1523, -4885, 2748, 5757, -538, 2421, -6388, 4235, -1383, -2030, 5659, 4894, 5260, 2392, 2548, 1455, 3252, 2811};
static INT_T L2_W1[L2_CTEMP] = {10094, 9956, 16075, 6974, 10175, 9699, 13183, 4375, 9195, 14069, 7134, 8253, 12871, 12751, 7453, 6728, 9530, 18404, 7295, 9357, 8840, 7842, 10315, 13118, 13024, 8228, 7788, 9726, 10236, 11723, 9542, 7451, 9822, 10150, 11307, 13256, 9472, 6752, 8555, 12180, 9339, 19637, 9817, 12491, 8945, 17197, 13108, 8752, 12493, 12432, 10086, 17906, 9242, 7041, 6779, 12607, 6482, 11634, 15465, 10888, 12301, 8698, 9213, 13377};
static INT_T L2_W2[L2_CTEMP] = {3871, 5651, 5750, 8225, 5556, 11611, 3455, 5812, 5268, 4948, 11909, 3863, 5018, 4935, 1977, 7664, 4014, 4255, 5355, 5632, 4884, 9463, 4477, 3726, 4206, 6160, 4394, 4323, 4448, 4974, 3335, 2398, 3272, 5695, 5549, 5582, 2009, 11998, 2926, 5308, 5140, 3071, 3146, 4846, 14159, 3995, 12855, 5261, 6205, 2153, 8252, 5726, 21547, 2982, 3434, 6239, 23142, 6721, 3740, 3289, 7340, 8160, 4496, 9885};
static INT_T L2_W3[L2_COUT] = {22096, 12094, 21617, 20652, 20780, 15576, 19265, 18774, 16671, 16868, 24720, 20844, 20840, 20362, 17108, 14834, 19480, 14267, 12983, 19978, 21522, 21886, 19198, 13253, 22059, 22662, 19706, 16743, 20464, 17757, 16747, 21536};
static INT_T L2_B1[L2_CTEMP] = {4476, 6149, 8751, -5404, 12528, 6211, -1550, -12338, -12936, 9605, -11560, 12407, -1503, 8070, 16402, 2586, 1153, -8352, -3714, 158, 4172, -11682, -2099, -16, -1931, -7126, 6813, 14726, -848, 2638, 1352, 6163, 11689, -5153, 3951, 277, 10315, -2849, 3552, 13743, -7739, 6446, -12143, 12703, -14417, 13021, -25, 4188, 16647, 8652, -6485, 2551, -6018, 2137, -5933, 2023, -17824, -11448, 7561, 5640, -1093, -5519, -11303, -1410};
static INT_T L2_B2[L2_CTEMP] = {5926, 14777, 13078, 10109, 14538, -488, -8207, -3093, -7210, 3133, -55, -2574, -3090, 12310, -3018, -4419, -4959, 14139, -5874, -6213, -2586, 7727, 18652, -9061, 7745, -6344, 3105, 12469, 15836, -1798, 22978, -7199, -2546, -1532, -12781, -6226, -2219, 7789, -4315, 7219, -105, 1176, -6240, 9839, -997, 2837, -5170, 6116, 11916, -6473, -2306, 519, -2364, -3783, -1658, 6430, -637, -2491, 19554, -5290, -3135, -2149, -3157, -3412};
static INT_T L2_B3[L2_COUT] = {5080, -3902, 7185, 8945, 4414, 15810, 18818, 15326, 18416, -4472, 7312, -13894, 6201, 3290, -8385, 5865, 4043, -21307, -13556, 19823, 16741, 8108, -8970, -2319, 12275, 4709, -232, 8347, 5687, 5768, 10816, 7495};

static SCALE_T L2_D1 = 5;
static SCALE_T L2_D2 = 4;
static SCALE_T L2_D3 = 6;
static INTM_T L2_Limit1 = 402653184L;
static INTM_T L2_Limit2 = 201326592L;
  
#ifdef SHIFT
  static L_SCALE_T L2_ShRU1 = 10; //1024
  static L_SCALE_T L2_ShRB1 = 3;  //8
  static L_SCALE_T L2_ShRX1 = 14; //16384
  static L_SCALE_T L2_ShRU2 = 9;  //512
  static L_SCALE_T L2_ShRB2 = 2;  //4
  static L_SCALE_T L2_ShRX2 = 13; //8192
  static L_SCALE_T L2_ShRU3 = 8;  //256
  static L_SCALE_T L2_ShRB3 = 2;  //4
  static L_SCALE_T L2_ShRW3 = 14; //16384
  static L_SCALE_T L2_ShLU1 = 0;  //1
  static L_SCALE_T L2_ShLB1 = 0;  //1
  static L_SCALE_T L2_ShLX1 = 0;  //1
  static L_SCALE_T L2_ShLU2 = 0;  //1
  static L_SCALE_T L2_ShLB2 = 0;  //1
  static L_SCALE_T L2_ShLX2 = 0;  //1
  static L_SCALE_T L2_ShLU3 = 0;  //1
  static L_SCALE_T L2_ShLB3 = 0;  //1
  static L_SCALE_T L2_ShLW3 = 0;  //1
#else
  static L_SCALE_T L2_ShRU1 = 1024;
  static L_SCALE_T L2_ShRB1 = 8;
  static L_SCALE_T L2_ShRX1 = 16384;
  static L_SCALE_T L2_ShRU2 = 512;
  static L_SCALE_T L2_ShRB2 = 4;
  static L_SCALE_T L2_ShRX2 = 8192;
  static L_SCALE_T L2_ShRU3 = 256;
  static L_SCALE_T L2_ShRB3 = 4;
  static L_SCALE_T L2_ShRW3 = 16384;
  static L_SCALE_T L2_ShLU1 = 1;
  static L_SCALE_T L2_ShLB1 = 1;
  static L_SCALE_T L2_ShLX1 = 1;
  static L_SCALE_T L2_ShLU2 = 1;
  static L_SCALE_T L2_ShLB2 = 1;
  static L_SCALE_T L2_ShLX2 = 1;
  static L_SCALE_T L2_ShLU3 = 1;
  static L_SCALE_T L2_ShLB3 = 1;
  static L_SCALE_T L2_ShLW3 = 1;
#endif