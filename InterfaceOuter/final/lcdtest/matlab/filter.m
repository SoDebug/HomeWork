BJ=floor(fir1(63,0.375)*32768);
fid = fopen('filter.txt', 'wt');
fprintf(fid, '%i,  ', BJ);