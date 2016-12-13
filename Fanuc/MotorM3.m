function M3r = MotorM3(in1,in2,in3,in4,in5,in6,in7,in8,in9,in10)
%MOTORM3
%    M3R = MOTORM3(IN1,IN2,IN3,IN4,IN5,IN6,IN7,IN8,IN9,IN10)

%    This function was generated by the Symbolic Math Toolbox version 5.5.
%    04-Dec-2014 19:06:57

Cx3 = in10(:,3);
Cx4 = in10(:,4);
Cx5 = in10(:,5);
Cx6 = in10(:,6);
Cy3 = in10(:,9);
Cy4 = in10(:,10);
Cy5 = in10(:,11);
Cy6 = in10(:,12);
Cz3 = in10(:,15);
Cz4 = in10(:,16);
Cz5 = in10(:,17);
Cz6 = in10(:,18);
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
Ma3 = in3(:,3);
Ma4 = in3(:,4);
Ma5 = in3(:,5);
Ma6 = in3(:,6);
th3 = in1(:,3);
th4 = in1(:,4);
th5 = in1(:,5);
th6 = in1(:,6);
t2484 = cos(th6);
t2486 = cos(th3);
t2487 = sin(th4);
t2488 = cos(th4);
t2489 = cos(th5);
t2490 = sin(th6);
t2491 = sin(th3);
t2492 = sin(th5);
t2506 = t2490.*t2487;
t2507 = t2484.*t2488.*t2489;
t2508 = t2506-t2507;
t2509 = t2486.*t2508;
t2510 = t2491.*t2492.*t2484;
t2485 = t2510+t2509;
t2511 = t2484.*t2487;
t2512 = t2490.*t2488.*t2489;
t2513 = t2511+t2512;
t2514 = t2486.*t2513;
t2515 = t2490.*t2491.*t2492;
t2493 = t2514-t2515;
t2496 = t2491.*t2489;
t2497 = t2492.*t2486.*t2488;
t2494 = t2496+t2497;
t2502 = t2491.*t2492;
t2503 = t2486.*t2488.*t2489;
t2495 = t2502-t2503;
t2498 = t2494.^2;
t2499 = t2491.^2;
t2500 = t2486.^2;
t2501 = t2487.^2;
t2504 = t2486.*t2489;
t2533 = t2491.*t2492.*t2488;
t2505 = t2504-t2533;
t2516 = t2488.^2;
t2517 = -Cz6+Ld1+Ld2+Ld4+Ld6;
t2518 = Cy5-Ld5;
t2519 = -Cx6+Ld3+Ld7;
t2520 = Cy6-Ld5;
t2521 = Cy4-Ld5;
t2522 = t2490.*t2488;
t2523 = t2484.*t2487.*t2489;
t2524 = t2522+t2523;
t2525 = t2491.*t2508;
t2554 = t2492.*t2484.*t2486;
t2526 = t2525-t2554;
t2527 = t2492.*t2486;
t2528 = t2491.*t2488.*t2489;
t2529 = t2527+t2528;
t2530 = Ld7.*t2486;
t2531 = Ld6.*t2491;
t2532 = t2530+t2531;
t2534 = Ld5.*t2505;
t2601 = t2492.*t2487.*t2532;
t2535 = t2534-t2601;
t2536 = t2484.*t2488;
t2571 = t2490.*t2487.*t2489;
t2537 = -t2571+t2536;
t2538 = t2491.*t2513;
t2539 = t2490.*t2492.*t2486;
t2540 = t2538+t2539;
t2541 = -Cz5+Ld1+Ld2+Ld4+Ld6;
t2542 = -Cx5+Ld3+Ld7;
t2543 = -Cz4+Ld1+Ld2+Ld4+Ld6;
t2544 = Cx4-Ld3;
t2545 = Ld5.*t2491.*t2487;
t2546 = Ma5.*t2495.*t2518;
t2582 = Ma5.*t2486.*t2487.*t2541;
t2547 = t2546-t2582;
t2548 = Ma6.*t2485.*t2520;
t2583 = Ma6.*t2493.*t2517;
t2549 = -t2583+t2548;
t2550 = Ma6.*t2494.*t2517;
t2578 = Ma6.*t2485.*t2519;
t2551 = t2550-t2578;
t2552 = Ma5.*t2494.*t2518;
t2584 = Ma5.*t2486.*t2487.*t2542;
t2553 = t2552-t2584;
t2555 = Ma6.*t2494.*t2520;
t2576 = Ma6.*t2493.*t2519;
t2556 = t2555-t2576;
t2557 = Ma4.*t2486.*t2487.*t2543;
t2558 = Ma4.*t2486.*t2488.*t2521;
t2559 = t2557+t2558;
t2560 = Ma4.*t2491.*t2543;
t2575 = Ma4.*t2486.*t2488.*t2544;
t2561 = t2560-t2575;
t2562 = Ma4.*t2491.*t2521;
t2563 = Ma4.*t2486.*t2487.*t2544;
t2564 = t2562+t2563;
t2565 = Ld6.*t2486;
t2567 = Ld7.*t2491;
t2566 = t2565-t2567;
t2568 = Ld5.*t2494;
t2569 = t2492.*t2487.*t2566;
t2570 = t2568+t2569;
t2572 = Ma5.*t2494.*t2541;
t2577 = Ma5.*t2495.*t2542;
t2573 = t2572-t2577;
t2574 = Ld5.*t2486.*t2487;
t2579 = t2494.*t2532;
t2580 = t2505.*t2566;
t2581 = t2580+t2579;
t2585 = Ma6.*t2485.*t2526;
t2586 = Ma6.*t2493.*t2540;
t2587 = Ma4.*t2491.*t2486.*t2516;
t2588 = Ma4.*t2491.*t2486.*t2501;
t2589 = Ma5.*t2491.*t2486.*t2501;
t2590 = t2585+t2586+t2587+t2588+t2589-Ma4.*t2491.*t2486-Ma5.*t2494.*t2505-Ma5.*t2495.*t2529-Ma6.*t2494.*t2505;
t2591 = t2505.^2;
t2592 = Ma3.*t2500;
t2593 = Ma3.*t2499;
t2594 = Cy3.*Ma3.*t2500;
t2595 = Ld5.*t2526;
t2672 = t2532.*t2524;
t2596 = t2595-t2672;
t2597 = Cy3.*Ma3.*t2499;
t2598 = Ld5.*t2529;
t2599 = t2487.*t2489.*t2532;
t2600 = t2598+t2599;
t2602 = Ld5.*t2540;
t2673 = t2532.*t2537;
t2603 = t2602-t2673;
t2670 = t2488.*t2532;
t2604 = t2545-t2670;
t2605 = Ld5.*t2491.*t2488;
t2606 = Ld6.*t2491.*t2487;
t2607 = t2605+t2606;
t2674 = Ld6.*t2491.*t2488;
t2608 = t2545-t2674;
t2609 = Ma4.*t2491.*t2487.*t2543;
t2610 = Ma4.*t2491.*t2488.*t2521;
t2611 = t2610+t2609;
t2612 = Ma6.*t2520.*t2526;
t2649 = Ma6.*t2540.*t2517;
t2613 = t2612-t2649;
t2614 = Ma5.*t2518.*t2529;
t2615 = Ma5.*t2491.*t2487.*t2541;
t2616 = t2614+t2615;
t2617 = Ma6.*t2505.*t2517;
t2618 = Ma6.*t2526.*t2519;
t2619 = t2617+t2618;
t2620 = Ma6.*t2540.*t2519;
t2621 = Ma6.*t2520.*t2505;
t2622 = t2620+t2621;
t2623 = Ma5.*t2505.*t2518;
t2624 = Ma5.*t2491.*t2487.*t2542;
t2625 = t2623+t2624;
t2626 = Ma4.*t2486.*t2543;
t2627 = Ma4.*t2491.*t2488.*t2544;
t2628 = t2626+t2627;
t2629 = Ma4.*t2486.*t2521;
t2641 = Ma4.*t2491.*t2487.*t2544;
t2630 = -t2641+t2629;
t2631 = Ld5.*t2485;
t2632 = Ld5.*t2495;
t2693 = t2487.*t2489.*t2566;
t2633 = t2632-t2693;
t2634 = Ld5.*t2493;
t2635 = Ma5.*t2505.*t2541;
t2642 = Ma5.*t2542.*t2529;
t2636 = -t2642+t2635;
t2637 = Ld5.*t2486.*t2488;
t2638 = Ld6.*t2486.*t2487;
t2639 = t2637+t2638;
t2640 = Ld5.*Ma4.*t2491.*t2486;
t2643 = t2529.*t2566;
t2644 = t2495.*t2532;
t2645 = t2643+t2644;
t2646 = t2493.*t2532;
t2698 = t2540.*t2566;
t2647 = t2646-t2698;
t2648 = -Cz3+Ld1+Ld2+Ld4;
t2650 = Ld6.*t2500;
t2651 = Ld6.*t2499;
t2652 = t2650+t2651;
t2653 = Cx3-Ld3;
t2654 = t2485.*t2532;
t2696 = t2526.*t2566;
t2655 = t2654-t2696;
t2656 = t2486.*t2487.*t2532;
t2695 = t2491.*t2487.*t2566;
t2657 = t2656-t2695;
t2658 = Ma6.*t2485.*t2524;
t2659 = Ma6.*t2493.*t2537;
t2660 = Ma5.*t2486.*t2487.*t2488;
t2661 = Ma5.*t2495.*t2487.*t2489;
t2662 = t2660+t2661+t2658+t2659-Ma5.*t2492.*t2494.*t2487-Ma6.*t2492.*t2494.*t2487;
t2663 = Ma6.*t2524.*t2526;
t2664 = Ma6.*t2540.*t2537;
t2665 = Ma5.*t2491.*t2487.*t2488;
t2666 = Ma5.*t2492.*t2487.*t2505;
t2667 = Ma6.*t2492.*t2487.*t2505;
t2668 = t2663+t2664+t2665+t2666+t2667-Ma5.*t2487.*t2489.*t2529;
t2669 = t2492.^2;
t2671 = Ma3.*t2491.*t2648;
t2675 = Ma5.*t2488.*t2542;
t2676 = Ma5.*t2492.*t2487.*t2518;
t2677 = t2675+t2676;
t2678 = Ma4.*t2487.*t2521;
t2933 = Ma4.*t2488.*t2543;
t2679 = t2678-t2933;
t2680 = Ma6.*t2524.*t2519;
t2681 = Ma6.*t2492.*t2487.*t2517;
t2682 = t2680+t2681;
t2683 = Ma6.*t2519.*t2537;
t2684 = Ma6.*t2492.*t2487.*t2520;
t2685 = t2683+t2684;
t2686 = Ma5.*t2488.*t2541;
t2694 = Ma5.*t2487.*t2489.*t2518;
t2687 = -t2694+t2686;
t2688 = Ma6.*t2520.*t2524;
t2697 = Ma6.*t2517.*t2537;
t2689 = t2688-t2697;
t2690 = Ma5.*t2487.*t2489.*t2542;
t2691 = Ma5.*t2492.*t2487.*t2541;
t2692 = t2690+t2691;
t2699 = Ma5.*t2535;
t2700 = -t2546+t2582+t2699;
t2701 = Ma6.*t2535;
t2702 = t2583-t2548+t2701;
t2703 = Ma5.*t2600;
t2704 = t2552-t2584+t2703;
t2705 = Ld5.*Ma4.*t2486;
t2706 = t2557+t2558+t2705;
t2707 = Ma6.*t2603;
t2708 = t2550-t2578+t2707;
t2709 = Ma6.*t2596;
t2710 = -t2555+t2576+t2709;
t2711 = Ma4.*t2607;
t2712 = t2562+t2563+t2711;
t2713 = Ma5.*t2604;
t2714 = t2572-t2577+t2713;
t2715 = Ma4.*t2608;
t2716 = t2560-t2575+t2715;
t2717 = Ma3.*t2486.*t2653;
t2718 = -t2602+t2673;
t2719 = -t2595+t2672;
t2720 = t2519.^2;
t2721 = Ma6.*t2720;
t2722 = Ma6.*t2520.*t2517;
t2723 = t2517.^2;
t2724 = Ma6.*t2723;
t2725 = t2520.^2;
t2726 = Ma6.*t2725;
t2727 = Ma6.*t2520.*t2519;
t2728 = -t2545+t2674;
t2729 = -t2545+t2670;
t2730 = t2518.^2;
t2731 = Ma5.*t2730;
t2732 = Cy3.^2;
t2733 = Ma3.*t2732;
t2734 = Ma3.*t2653.*t2648;
t2735 = t2543.^2;
t2736 = Ma4.*t2735;
t2737 = Ma4.*t2543.*t2544;
t2738 = t2544.^2;
t2739 = Ma4.*t2738;
t2740 = t2521.^2;
t2741 = Ma4.*t2740;
t2742 = Ma4.*t2521.*t2543;
t2743 = Ma5.*t2542.*t2518;
t2744 = Ma5.*t2541.*t2518;
t2745 = t2541.^2;
t2746 = Ma5.*t2745;
t2747 = t2542.^2;
t2748 = Ma5.*t2747;
t2749 = t2653.^2;
t2750 = Ma3.*t2749;
t2751 = I3_33+t2750+t2733;
t2752 = t2486.*t2751;
t2753 = I3_13+t2734;
t2754 = t2752-t2491.*t2753;
t2755 = I6_22+t2721+t2724;
t2756 = t2493.*t2755;
t2757 = I6_12+t2727;
t2758 = I6_32+t2722;
t2759 = Ma6.*t2517.*t2535;
t2760 = Ma6.*t2718;
t2761 = -t2550+t2578+t2760;
t2762 = Ma6.*t2719;
t2763 = t2555-t2576+t2762;
t2764 = I5_11+t2731+t2746;
t2765 = t2494.*t2764;
t2801 = Ma5.*t2541.*t2542;
t2766 = I5_31-t2801;
t2767 = t2495.*t2766;
t2768 = Ma5.*t2518.*t2600;
t2769 = I5_21+t2743;
t2770 = I6_33+t2721+t2726;
t2771 = t2485.*t2770;
t2772 = I6_23+t2722;
t2781 = Ma6.*t2517.*t2519;
t2773 = I6_13-t2781;
t2774 = t2494.*t2773;
t2775 = Ma6.*t2519.*t2718;
t2834 = t2493.*t2772;
t2835 = Ma6.*t2520.*t2535;
t2776 = t2771+t2774+t2775-t2834-t2835;
t2777 = Ma4.*t2728;
t2778 = -t2560+t2575+t2777;
t2779 = I6_11+t2724+t2726;
t2780 = t2494.*t2779;
t2782 = I6_21+t2727;
t2783 = Ma6.*t2520.*t2719;
t2784 = Ma5.*t2729;
t2785 = -t2572+t2577+t2784;
t2786 = I4_11+t2741+t2736;
t2804 = Ma4.*t2521.*t2544;
t2787 = I4_21-t2804;
t2788 = t2486.*t2487.*t2787;
t2789 = Ma4.*t2543.*t2728;
t2790 = I4_31+t2737;
t2791 = t2486.*t2488.*t2790;
t2792 = t2791+t2788+t2789-t2491.*t2786-Ma4.*t2521.*t2607;
t2793 = t2648.^2;
t2794 = Ma3.*t2793;
t2795 = I3_11+t2733+t2794;
t2796 = t2491.*t2795;
t2797 = I3_31+t2734;
t2798 = t2796-t2486.*t2797;
t2799 = I5_33+t2731+t2748;
t2800 = t2495.*t2799;
t2802 = Ma5.*t2542.*t2729;
t2803 = I5_23+t2744;
t2805 = Ma4.*t2544.*t2607;
t2806 = I4_22+t2736+t2739;
t2807 = t2486.*t2487.*t2806;
t2808 = I4_32+t2742;
t2809 = t2486.*t2488.*t2808;
t2810 = Ld5.*Ma4.*t2486.*t2543;
t2811 = I4_13+t2737;
t2812 = Ma4.*t2544.*t2728;
t2813 = I4_33+t2741+t2739;
t2814 = t2486.*t2488.*t2813;
t2815 = I4_23+t2742;
t2816 = t2486.*t2487.*t2815;
t2817 = Ld5.*Ma4.*t2486.*t2521;
t2836 = t2491.*t2811;
t2818 = t2812+t2814+t2816+t2817-t2836;
t2819 = I5_12+t2743;
t2820 = t2494.*t2819;
t2821 = I5_32+t2744;
t2822 = t2495.*t2821;
t2823 = Ma5.*t2542.*t2600;
t2824 = I5_22+t2746+t2748;
t2832 = Ma5.*t2541.*t2535;
t2833 = t2486.*t2487.*t2824;
t2825 = t2820+t2822+t2823-t2832-t2833;
t2826 = t2494.*t2757;
t2827 = t2485.*t2758;
t2828 = Ma6.*t2519.*t2719;
t2829 = -t2756-t2759+t2826+t2827+t2828;
t2830 = I4_12-t2804;
t2831 = t2810+t2805+t2807+t2809-t2491.*t2830;
t2837 = t2765+t2767+t2768-Ma5.*t2541.*t2729-t2486.*t2487.*t2769;
t2838 = I6_31-t2781;
t2839 = t2485.*t2838;
t2840 = t2780+t2783+t2839-t2493.*t2782-Ma6.*t2517.*t2718;
t2841 = I5_13-t2801;
t2842 = t2494.*t2841;
t2843 = t2800+t2802+t2842-Ma5.*t2535.*t2518-t2486.*t2487.*t2803;
t2853 = t2524.*t2566;
t2844 = t2631-t2853;
t2857 = t2488.*t2566;
t2845 = t2574-t2857;
t2846 = Ma6.*t2570;
t2847 = -t2612+t2649+t2846;
t2848 = Ma5.*t2570;
t2849 = t2614+t2615+t2848;
t2867 = Ma5.*t2633;
t2850 = t2623+t2624-t2867;
t2863 = t2537.*t2566;
t2869 = t2634-t2863;
t2851 = Ma6.*t2869;
t2852 = t2617+t2618+t2851;
t2864 = Ma6.*t2844;
t2854 = t2620+t2621-t2864;
t2855 = Ld5.*Ma4.*t2491;
t2856 = t2610+t2609+t2855;
t2858 = Ma5.*t2845;
t2865 = Ld6.*t2486.*t2488;
t2870 = t2574-t2865;
t2859 = Ma4.*t2870;
t2860 = t2626+t2627+t2859;
t2861 = Ma4.*t2639;
t2862 = -t2641+t2629+t2861;
t2866 = Ma3.*t2486.*t2648;
t2868 = Ma3.*t2491.*t2653;
t2871 = t2491.*t2751;
t2872 = t2486.*t2753;
t2873 = t2871+t2872;
t2874 = t2540.*t2755;
t2875 = t2505.*t2757;
t2876 = Ma6.*t2570.*t2517;
t2916 = t2526.*t2758;
t2877 = t2874+t2875+t2876-t2916-Ma6.*t2519.*t2844;
t2878 = -t2634+t2863;
t2879 = -t2631+t2853;
t2880 = t2505.*t2764;
t2881 = t2529.*t2766;
t2882 = t2491.*t2487.*t2769;
t2883 = t2540.*t2772;
t2884 = t2505.*t2773;
t2885 = Ma6.*t2520.*t2570;
t2886 = -t2574+t2865;
t2887 = t2486.*t2786;
t2888 = Ma4.*t2521.*t2639;
t2889 = t2491.*t2487.*t2787;
t2890 = t2491.*t2488.*t2790;
t2891 = t2505.*t2779;
t2892 = t2540.*t2782;
t2893 = -t2574+t2857;
t2894 = t2486.*t2795;
t2895 = t2491.*t2797;
t2896 = t2894+t2895;
t2897 = t2529.*t2799;
t2898 = t2505.*t2841;
t2899 = t2491.*t2487.*t2803;
t2900 = Ma5.*t2570.*t2518;
t2901 = t2486.*t2830;
t2902 = t2491.*t2487.*t2806;
t2903 = t2491.*t2488.*t2808;
t2904 = Ld5.*Ma4.*t2491.*t2543;
t2917 = Ma4.*t2544.*t2639;
t2905 = t2901+t2902+t2903+t2904-t2917;
t2906 = t2486.*t2811;
t2907 = t2491.*t2487.*t2815;
t2908 = t2491.*t2488.*t2813;
t2909 = Ld5.*Ma4.*t2491.*t2521;
t2910 = t2505.*t2819;
t2911 = t2529.*t2821;
t2912 = Ma5.*t2541.*t2570;
t2913 = t2491.*t2487.*t2824;
t2918 = Ma5.*t2542.*t2633;
t2914 = t2910+t2911+t2912+t2913-t2918;
t2952 = Cy3.*Ma3.*t2653;
t2915 = I3_12-t2952;
t2919 = Ma6.*t2519.*t2878;
t2920 = t2883+t2884+t2885+t2919-t2526.*t2770;
t2921 = t2906+t2907+t2908+t2909-Ma4.*t2544.*t2886;
t2922 = Ma5.*t2893;
t2923 = t2642-t2635+t2922;
t2924 = Cy3.*Ma3.*t2648;
t2925 = I3_32+t2924;
t2926 = Ma6.*t2879;
t2927 = t2620+t2621+t2926;
t2928 = t2617+t2618-Ma6.*t2878;
t2929 = Ma6.*t2520.*t2879;
t2930 = t2891+t2892+t2929-t2526.*t2838-Ma6.*t2517.*t2878;
t2931 = Ma5.*t2542.*t2893;
t2932 = t2897+t2898+t2899+t2900+t2931;
t2934 = Ma4.*t2486.*t2516.*t2544;
t2935 = Ma4.*t2486.*t2501.*t2544;
t2936 = Ma4.*t2652;
t2937 = t2678-t2933+t2936;
t2938 = Ma6.*t2655;
t2939 = t2683+t2684+t2938;
t2940 = Ma5.*t2581;
t2941 = t2694-t2686+t2940;
t2951 = Ma6.*t2647;
t2942 = t2680+t2681-t2951;
t2943 = Ma6.*t2581;
t2944 = t2688-t2697+t2943;
t2945 = Ma5.*t2645;
t2946 = t2675+t2676+t2945;
t2950 = Ma5.*t2657;
t2947 = t2690+t2691-t2950;
t2948 = Ma4.*t2491.*t2516.*t2544;
t2949 = Ma4.*t2491.*t2501.*t2544;
t2953 = t2537.*t2782;
t2954 = Ma6.*t2520.*t2655;
t2955 = t2492.*t2487.*t2779;
t2998 = t2524.*t2838;
t2956 = t2953+t2954+t2955-t2998-Ma6.*t2517.*t2647;
t2957 = I3_21-t2952;
t2958 = t2488.*t2803;
t2959 = t2492.*t2487.*t2841;
t2960 = Ma5.*t2542.*t2657;
t2999 = t2487.*t2489.*t2799;
t3000 = Ma5.*t2518.*t2581;
t2961 = t2960+t2958+t2959-t2999-t3000;
t2962 = t2537.*t2755;
t2963 = t2492.*t2487.*t2757;
t2964 = Ma6.*t2519.*t2655;
t2987 = t2524.*t2758;
t2988 = Ma6.*t2517.*t2581;
t2965 = t2962+t2963+t2964-t2987-t2988;
t2966 = I3_23+t2924;
t2967 = t2488.*t2769;
t2968 = t2492.*t2487.*t2764;
t2969 = Ma5.*t2518.*t2645;
t2996 = t2487.*t2489.*t2766;
t2997 = Ma5.*t2541.*t2657;
t2970 = t2967+t2968+t2969-t2996-t2997;
t2971 = t2537.*t2772;
t2972 = t2492.*t2487.*t2773;
t2973 = Ma6.*t2519.*t2647;
t2989 = t2524.*t2770;
t2990 = Ma6.*t2520.*t2581;
t2974 = t2971+t2972-t2990+t2973-t2989;
t2975 = t2487.*t2790;
t2976 = t2975-t2488.*t2787;
t2977 = t2487.*t2808;
t2978 = Ma4.*t2543.*t2652;
t2991 = t2488.*t2806;
t2979 = -t2991+t2977+t2978;
t2980 = t2487.*t2813;
t2981 = Ma4.*t2521.*t2652;
t2993 = t2488.*t2815;
t2982 = t2980+t2981-t2993;
t2983 = t2488.*t2824;
t2984 = Ma5.*t2542.*t2645;
t2985 = t2492.*t2487.*t2819;
t2994 = Ma5.*t2541.*t2581;
t2995 = t2487.*t2489.*t2821;
t2986 = t2983+t2984+t2985-t2994-t2995;
t2992 = -t2646+t2698;
M3r = reshape([t2592+t2593+Ma4.*t2499+Ma5.*t2498+Ma6.*t2498+Ma5.*t2495.^2+Ma6.*t2493.^2+Ma6.*t2485.^2+Ma4.*t2500.*t2501+Ma4.*t2500.*t2516+Ma5.*t2500.*t2501,t2590,t2662,t2494.*t2700-t2485.*t2710+t2494.*t2702+t2491.*t2706+t2495.*t2704-t2493.*t2708-t2486.*t2488.*t2712-t2486.*t2487.*t2714-t2486.*t2487.*t2716,t2594+t2597+t2493.*t2852-t2495.*t2850+t2491.*t2856-t2485.*t2854+t2494.*t2847+t2494.*t2849+t2486.*t2487.*(-t2642+t2635+t2858)+t2486.*t2487.*t2860+t2486.*t2488.*t2862,t2671-t2717-t2934-t2935+t2493.*t2942-t2494.*t2941-t2491.*t2937-t2494.*t2944-t2495.*t2946-t2485.*t2939+t2486.*t2487.*t2947,t2590,t2592+t2593+Ma4.*t2500+Ma5.*t2591+Ma6.*t2591+Ma5.*t2529.^2+Ma6.*t2540.^2+Ma6.*t2526.^2+Ma4.*t2499.*t2501+Ma4.*t2499.*t2516+Ma5.*t2499.*t2501,t2668,-t2594-t2597-t2486.*t2706-t2505.*t2700-t2505.*t2702-t2526.*t2710-t2540.*t2708-t2529.*t2704-t2491.*t2488.*t2712-t2491.*t2487.*t2714-t2491.*t2487.*t2716,-t2486.*t2856+t2540.*t2852-t2505.*t2847+t2529.*t2850-t2526.*t2854-t2505.*t2849+t2491.*t2487.*(-t2642+t2635+t2858)+t2491.*t2487.*t2860+t2491.*t2488.*t2862,-t2866-t2868-t2948-t2949+t2486.*t2937+t2540.*t2942+t2505.*t2941+t2505.*t2944-t2526.*t2939+t2529.*t2946+t2491.*t2487.*t2947,t2662,t2668,Ma3+Ma4.*t2501+Ma4.*t2516+Ma5.*t2516+Ma6.*t2524.^2+Ma6.*t2537.^2+Ma5.*t2501.*t2669+Ma6.*t2501.*t2669+Ma5.*t2489.^2.*t2501,-t2671+t2717+t2487.*t2712-t2488.*t2714-t2488.*t2716-t2524.*t2710-t2537.*t2708-t2492.*t2487.*t2700-t2492.*t2487.*t2702+t2487.*t2489.*t2704,t2866+t2868+t2488.*t2860-t2487.*t2862-t2524.*t2854+t2537.*t2852+t2488.*(-t2642+t2635+t2858)-t2492.*t2487.*t2847-t2487.*t2489.*t2850-t2492.*t2487.*t2849,t2488.*t2947+t2537.*t2942-t2524.*t2939+t2492.*t2487.*t2941+t2492.*t2487.*t2944-t2487.*t2489.*t2946,t2640+t2493.*t2551-t2495.*t2553-t2491.*t2559-t2485.*t2556+t2494.*t2547+t2494.*t2549+Ma5.*t2494.*t2535+Ma5.*t2495.*t2600+Ma6.*t2494.*t2535-Ma6.*t2485.*t2596-Ma6.*t2493.*t2603+t2486.*t2487.*t2561+t2486.*t2487.*t2573+t2486.*t2488.*t2564-Ma4.*t2486.*t2487.*t2608-Ma4.*t2486.*t2488.*t2607-Ma5.*t2486.*t2487.*t2604,-t2594-t2597-t2491.*t2611+t2485.*t2622+t2494.*t2613-t2494.*t2616+t2495.*t2625-t2493.*t2619-Ld5.*Ma4.*t2500-Ma5.*t2505.*t2535-Ma5.*t2529.*t2600-Ma6.*t2505.*t2535-Ma6.*t2526.*t2596-Ma6.*t2540.*t2603-t2486.*t2488.*t2630-t2486.*t2487.*t2636-t2486.*t2487.*t2628-Ma4.*t2491.*t2487.*t2608-Ma4.*t2491.*t2488.*t2607-Ma5.*t2491.*t2487.*t2604,-t2671+t2717+t2934+t2935-t2493.*t2682+t2491.*t2679+t2485.*t2685-t2494.*t2687+t2495.*t2677+t2494.*t2689+Ma4.*t2487.*t2607-Ma4.*t2488.*t2608-Ma5.*t2488.*t2604-Ma6.*t2524.*t2596-Ma6.*t2537.*t2603-t2486.*t2487.*t2692-Ma5.*t2492.*t2487.*t2535+Ma5.*t2487.*t2489.*t2600-Ma6.*t2492.*t2487.*t2535,t2494.*(t2780+t2783+t2485.*(I6_31-Ma6.*t2517.*t2519)-t2493.*t2782-Ma6.*t2517.*t2718)+t2494.*(t2765+t2767+t2768-t2486.*t2487.*t2769+Ma5.*t2541.*(t2545-t2670))+t2493.*(t2756+t2759-t2494.*t2757-t2485.*t2758+Ma6.*t2519.*t2596)-t2491.*t2792+t2486.*t2754+t2485.*t2776+t2491.*t2798+t2535.*t2700+t2535.*t2702+t2600.*t2704+t2607.*t2712+t2761.*t2718+t2763.*t2719+t2729.*t2785+t2728.*t2778+t2495.*(t2800+t2802+t2494.*(I5_13-Ma5.*t2541.*t2542)-Ma5.*t2535.*t2518-t2486.*t2487.*t2803)+t2486.*t2487.*(t2810+t2805+t2807+t2809-t2491.*(I4_12-Ma4.*t2521.*t2544))+Ld5.*t2486.*t2706-t2486.*t2487.*t2825+t2486.*t2488.*t2818,t2486.*t2873-t2491.*t2896+t2493.*t2877+t2535.*t2847+t2535.*t2849-t2600.*t2850-t2607.*t2862+t2718.*t2852+t2728.*t2860-t2719.*t2854-t2485.*(t2883+t2884+t2885-t2526.*t2770-Ma6.*t2519.*t2869)-t2494.*(t2891+t2892-t2526.*t2838-Ma6.*t2520.*t2844+Ma6.*t2517.*t2869)-t2491.*(t2890+t2887+t2888+t2889+Ma4.*t2543.*t2870)-t2495.*(t2897+t2898+t2899+t2900-Ma5.*t2542.*t2845)-t2494.*(t2880+t2881+t2882-Ma5.*t2518.*t2633+Ma5.*t2541.*t2845)+t2729.*(-t2642+t2635+t2858)+t2486.*t2488.*(t2906+t2907+t2908+t2909+Ma4.*t2544.*(t2574-t2865))+Ld5.*t2486.*t2856+t2486.*t2487.*t2905+t2486.*t2487.*t2914,-t2494.*t2970-t2495.*t2961-t2491.*t2957+t2491.*t2976+t2493.*t2965-t2485.*t2974-t2494.*t2956+t2486.*t2966-t2535.*t2941-t2535.*t2944-t2600.*t2946+t2718.*t2942-t2719.*t2939+t2729.*t2947-Ld5.*t2486.*t2937-t2486.*t2488.*t2982+t2486.*t2487.*t2986-t2486.*t2487.*t2979+Ma4.*t2488.*t2544.*t2607-Ma4.*t2487.*t2544.*t2728,t2594+t2597+t2486.*t2559+t2540.*t2551-t2505.*t2547-t2505.*t2549-t2526.*t2556+t2553.*t2529+Ma6.*t2493.*(t2634-t2537.*t2566)+Ld5.*Ma4.*t2499+Ma5.*t2494.*t2570+Ma5.*t2495.*t2633+Ma6.*t2494.*t2570+Ma6.*t2485.*t2844+t2491.*t2487.*t2561+t2491.*t2487.*t2573+t2491.*t2488.*t2564+Ma4.*t2486.*t2488.*t2639+Ma5.*t2486.*t2487.*t2845+Ma4.*t2486.*t2487.*(t2574-Ld6.*t2486.*t2488),-t2640+t2486.*t2611-t2505.*t2613+t2505.*t2616+t2526.*t2622-t2540.*t2619-t2529.*t2625+Ma6.*t2540.*(t2634-t2537.*t2566)-Ma5.*t2505.*t2570-Ma6.*t2505.*t2570-Ma5.*t2529.*t2633+Ma6.*t2526.*t2844-t2491.*t2488.*t2630-t2491.*t2487.*t2636-t2491.*t2487.*t2628+Ma4.*t2491.*t2488.*t2639+Ma5.*t2491.*t2487.*t2845+Ma4.*t2491.*t2487.*(t2574-Ld6.*t2486.*t2488),t2866+t2868+t2948+t2949-t2486.*t2679-t2540.*t2682+t2505.*t2687+t2526.*t2685-t2505.*t2689-t2529.*t2677+Ma6.*t2537.*(t2634-t2537.*t2566)+Ma4.*t2488.*(t2574-Ld6.*t2486.*t2488)-Ma4.*t2487.*t2639+Ma5.*t2488.*t2845+Ma6.*t2524.*t2844-t2491.*t2487.*t2692-Ma5.*t2492.*t2487.*t2570-Ma6.*t2492.*t2487.*t2570+Ma5.*t2487.*t2489.*t2633,t2778.*(t2574-Ld6.*t2486.*t2488)+t2491.*t2754+t2486.*t2792-t2486.*t2798+t2570.*t2700+t2570.*t2702+t2526.*t2776-t2505.*t2840+t2633.*t2704-t2540.*t2829-t2505.*t2837-t2639.*t2712-t2529.*t2843+t2763.*t2844+t2785.*t2845+t2761.*(t2634-t2537.*t2566)+Ld5.*t2491.*t2706+t2491.*t2487.*t2831-t2491.*t2487.*t2825+t2491.*t2488.*t2818,-t2886.*(t2626+t2627-Ma4.*t2886)+t2491.*t2873+t2486.*t2896+t2540.*t2877+t2570.*t2847+t2570.*t2849+t2505.*t2930-t2526.*t2920-t2633.*t2850+t2529.*t2932+t2639.*t2862+t2893.*t2923-t2878.*t2928+t2879.*t2927+t2486.*(t2890+t2887+t2888+t2889-Ma4.*t2543.*t2886)+t2505.*(t2880+t2881+t2882-Ma5.*t2518.*t2633+Ma5.*t2541.*(t2574-t2857))+Ld5.*t2491.*t2856+t2491.*t2488.*t2921+t2491.*t2487.*t2905+t2491.*t2487.*t2914,t2491.*t2966+t2486.*t2957-t2486.*t2976+t2505.*t2970-t2570.*t2941+t2540.*t2965-t2570.*t2944+t2505.*t2956+t2529.*t2961-t2526.*t2974-t2633.*t2946-t2878.*t2942-t2893.*t2947+t2879.*t2939-Ld5.*t2491.*t2937-t2491.*t2488.*t2982+t2491.*t2487.*t2986-t2491.*t2487.*t2979-Ma4.*t2488.*t2544.*t2639+Ma4.*t2487.*t2544.*t2886,t2671+t2488.*t2561-t2487.*t2564+t2488.*t2573+t2551.*t2537-t2524.*t2556-Ma3.*t2486.*t2653-Ma4.*t2491.*t2652-Ma5.*t2494.*t2581-Ma6.*t2494.*t2581-Ma5.*t2495.*t2645-Ma6.*t2493.*t2647-Ma6.*t2485.*t2655-t2492.*t2487.*t2547-t2487.*t2489.*t2553+t2492.*t2487.*(t2583-t2548)-Ma5.*t2486.*t2487.*t2657,t2487.*t2630-t2488.*t2636-t2488.*t2628+t2524.*t2622-t2537.*t2619-Ma3.*t2491.*t2653-Ma3.*t2486.*t2648+Ma4.*t2486.*t2652+Ma5.*t2505.*t2581+Ma6.*t2505.*t2581+Ma5.*t2529.*t2645-Ma6.*t2540.*t2647-Ma6.*t2526.*t2655-t2492.*t2487.*t2613+t2492.*t2487.*t2616+t2487.*t2489.*t2625-Ma5.*t2491.*t2487.*t2657,-t2488.*t2692+t2524.*t2685-t2537.*t2682-Ma5.*t2488.*t2657-Ma6.*t2524.*t2655-Ma6.*t2537.*t2647+t2492.*t2487.*t2687-t2492.*t2487.*t2689+t2487.*t2489.*t2677+Ma5.*t2492.*t2487.*t2581+Ma6.*t2492.*t2487.*t2581-Ma5.*t2487.*t2489.*t2645,-t2581.*t2700-t2581.*t2702+t2524.*t2776+t2488.*t2831-t2488.*t2825-t2487.*t2818-t2652.*t2706-t2645.*t2704-t2491.*t2915-t2647.*t2761-t2655.*t2763+t2486.*t2925-t2537.*t2829-t2657.*t2785-t2492.*t2487.*t2840-t2492.*t2487.*t2837+t2487.*t2489.*t2843,t2491.*t2925-t2487.*t2921+t2486.*t2915-t2581.*t2847+t2488.*t2905+t2488.*t2914-t2581.*t2849-t2524.*t2920+t2645.*t2850-t2652.*t2856+t2657.*t2923+t2655.*t2927-t2647.*t2928+t2537.*(t2874+t2875+t2876-t2916+Ma6.*t2519.*t2879)+t2492.*t2487.*(t2880+t2881+t2882-Ma5.*t2518.*t2633-Ma5.*t2541.*t2893)+t2492.*t2487.*t2930-t2487.*t2489.*t2932,I3_22+t2750+t2794+t2992.*(t2680+t2681+Ma6.*t2992)+t2487.*t2982+t2488.*t2986-t2488.*t2979+t2581.*t2941-t2524.*t2974+t2581.*t2944+t2537.*t2965+t2652.*t2937+t2645.*t2946+t2655.*t2939-t2657.*t2947+t2492.*t2487.*(t2953+t2954+t2955-t2998+Ma6.*t2517.*t2992)+t2492.*t2487.*t2970-t2487.*t2489.*t2961],[6, 6]);