function speechproc()

    % ���峣��
    FL = 160;                % ֡��
    WL = 240;               % ����
    P = 10;                 % Ԥ��ϵ������
    s = readspeech('./output_files/output_files.pcm',100000);   % ��������s,���������ƣ�Pulse Code Modulation, PCM��
    %s = readspeech('Young.pcm',44100000);
    L = length(s);          % ������������
    FN = floor(L/FL)-2;     % ����֡��
    % Ԥ����ؽ��˲���
    exc = zeros(L,1);       % �����źţ�Ԥ����
    zi_pre = zeros(P,1);    % Ԥ���˲�����״̬
    s_rec = zeros(L,1);     % �ؽ�����
    zi_rec = zeros(P,1);
    % �ϳ��˲���
    exc_syn = zeros(L,1);   % �ϳɵļ����źţ����崮��
    s_syn = zeros(L,1);     % �ϳ�����
    zi_syn = zeros(P,1);
    % ����������˲���
    exc_syn_t = zeros(L,1);   % �ϳɵļ����źţ����崮��
    s_syn_t = zeros(L,1);     % �ϳ�����
    zi_syn_t = zeros(P,1);
    % ���ٲ�����˲����������ٶȼ���һ����
    exc_syn_v = zeros(2*L,1);   % �ϳɵļ����źţ����崮��
    s_syn_v = zeros(2*L,1);     % �ϳ�����
    zi_syn_v = zeros(P,1);

    hw = hamming(WL);       % ������
    
    pos = 2*FL+1;           % �����ź���ʼλ��
    
    FL_v = FL*2;            % ���ٲ������֡��
    pos_v = 2*FL_v+1;       % ���ٲ���������ź���ʼλ��
    
    pos_t = 2*FL+1;         % ��������ټ����ź���ʼλ��
    % ���δ���ÿ֡����
    for n = 3:FN

        % ����Ԥ��ϵ��������Ҫ���գ�
        s_w = s(n*FL-WL+1:n*FL).*hw;    %��������Ȩ�������
        [A, E] = lpc(s_w, P);            %������Ԥ�ⷨ����P��Ԥ��ϵ��
                                        % A��Ԥ��ϵ����E�ᱻ��������ϳɼ���������

        if n == 27
        % (3) �ڴ�λ��д���򣬹۲�Ԥ��ϵͳ���㼫��ͼ
            figure;
            zplane(A, 1);
            title("Ԥ��ϵͳ���㼫��ͼ");
        end
        
        s_f = s((n-1)*FL+1:n*FL);       % ��֡�����������Ҫ����������

        % (4) �ڴ�λ��д������filter����s_f���㼤����ע�Ᵽ���˲���״̬
        
        [exc((n-1)*FL+1:n*FL), zi_pre] = filter(A, 1, s_f, zi_pre);

        % (5) �ڴ�λ��д������filter������exc�ؽ�������ע�Ᵽ���˲���״̬
      
        [s_rec((n-1)*FL+1:n*FL), zi_rec] = filter(1, A, exc((n-1)*FL+1:n*FL), zi_rec);

        % ע������ֻ���ڵõ�exc��Ż������ȷ
        s_Pitch = exc(n*FL-222:n*FL);
        PT = findpitch(s_Pitch);    % �����������PT����Ҫ�����գ�
        G = sqrt(E*PT);           % ����ϳɼ���������G����Ҫ�����գ�

        
        % (10) �ڴ�λ��д�������ɺϳɼ��������ü�����filter���������ϳ�����

        while pos <= n * FL
            exc_syn(pos) = G;
            pos = pos + PT;
        end
        [s_syn((n-1)*FL+1:n*FL), zi_syn] = filter(1, A, exc_syn((n-1)*FL+1:n*FL), zi_syn);

        % (11) ���ı�������ں�Ԥ��ϵ�������ϳɼ����ĳ�������һ��������Ϊfilter
        % ������õ��µĺϳ���������һ���ǲ����ٶȱ����ˣ�������û�б䡣

        while pos_v <= n * FL_v
            exc_syn_v(pos_v) = G;
            pos_v = pos_v + PT;
        end
        [s_syn_v((n-1)*FL_v+1:n*FL_v), zi_syn_v] = filter(1, A, exc_syn_v((n-1)*FL_v+1:n*FL_v), zi_syn_v);
        
        % (13) ���������ڼ�Сһ�룬�������Ƶ������150Hz�����ºϳ�������������ɶ���ܡ�
        while pos_t <= n * FL
            exc_syn_t(pos_t) = G;
            pos_t = pos_t + round(PT / 2);
        end
        [z, p, k] = tf2zpk(1, A);
        p = p .* exp(1i * sign(imag(p)) * 150 * 2 * pi / 8000);
        [~, A1] = zp2tf(z, p, k);
        [s_syn_t((n-1)*FL+1:n*FL), zi_syn_t] = filter(1, A1, exc_syn_t((n-1)*FL+1:n*FL), zi_syn_t);
        
    end

    % (6) �ڴ�λ��д������һ�� s ��exc �� s_rec �к����𣬽�����������
    % ��������������ĿҲ������������д���������ر�ע��
    
    % ������(6)���3���ź�
    % sound([s;exc;s_rec] / 32768, 8000);

    % �������������ɵ�ȫ���źţ��ֱ���:
    % ԭʼ����s, �����ź�exc, �ؽ�����s_rec, �ϳ�����s_syn, ���ٲ����s_syn_v, ���������s_syn_t
    % sound([s;exc;s_rec;s_syn;s_syn_v;s_syn_t] / 32768, 8000);
    sound([s;s_rec;s_syn;s_syn_v;s_syn_t] / 32768, 8000);

    % ����(6)ʱ����ͼ
    time = (0 : L - 1)' / 8000;
    figure;
    subplot(3, 1, 1);
    plot(time, s);
    % �鿴ϸ�ڲ���
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s(n)');
    subplot(3, 1, 2);
    plot(time, exc);
    % �鿴ϸ�ڲ���
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('exc(n)');
    subplot(3, 1, 3);
    plot(time, s_rec);
    % �鿴ϸ�ڲ���
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s\_rec(n)');
    
    % ����(6)Ƶ����ͼ
    figure;
    fft_freq = 8000 * (0 : (L / 2))' / L;
    subplot(3, 1, 1);
    S = abs(fft(s) / L);
    S = S(1 : L / 2 + 1);
    S(2 : end - 1) = 2 * S(2 : end - 1);
    plot(fft_freq, S);
    ylabel('s(n)����Ƶ��');
    subplot(3, 1, 2);
    EXC = abs(fft(exc) / L);
    EXC = EXC(1 : L / 2 + 1);
    EXC(2 : end - 1) = 2 * EXC(2 : end - 1);
    plot(fft_freq, EXC);
    ylabel('exc(n)����Ƶ��');
    subplot(3, 1, 3);
    S_REC = abs(fft(s_rec) / L);
    S_REC = S_REC(1 : L / 2 + 1);
    S_REC(2 : end - 1) = 2 * S_REC(2 : end - 1);
    plot(fft_freq, S_REC);
    ylabel('s\_rec(n)����Ƶ��');

    % ����(10)ʱ����ͼ
    time = (0 : L - 1)' / 8000;
    figure;
    subplot(2, 1, 1);
    plot(time, s);
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s(n)');
    subplot(2, 1, 2);
    plot(time, s_syn);
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s\_syn(n)');
    
    % ����(10)Ƶ����ͼ
    figure;
    fft_freq = 8000 * (0 : (L / 2))' / L;
    subplot(2, 1, 1);
    S = abs(fft(s) / L);
    S = S(1 : L / 2 + 1);
    S(2 : end - 1) = 2 * S(2 : end - 1);
    plot(fft_freq, S);
    ylabel('s(n)����Ƶ��');
    subplot(2, 1, 2);
    S_SYN = abs(fft(s_syn) / L);
    S_SYN = S_SYN(1 : L / 2 + 1);
    S_SYN(2 : end - 1) = 2 * S_SYN(2 : end - 1);
    plot(fft_freq, S_SYN);
    ylabel('s\_syn(n)����Ƶ��');
    
    % ����(11)��(13)ʱ����ͼ
    time = (0 : L - 1)' / 8000;
    time1 = (0 : 2 * L - 1)' / 8000;
    figure;
    subplot(4, 1, 1);
    plot(time, s);
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s(n)');
    subplot(4, 1, 2);
    plot(time, s_syn);
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s\_syn(n)');
    subplot(4, 1, 3);
    plot(time1, s_syn_v);
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s\_syn\_v(n)');
    subplot(4, 1, 4);
    plot(time, s_syn_t);
    % set(gca, 'XLim', [0.5, 0.55]);
    ylabel('s\_syn\_t(n)');
    
    % ����(11)��(13)Ƶ����ͼ
    figure;
    fft_freq = 8000 * (0 : (L / 2))' / L;
    fft_freq1 = 2 * 8000 * (0 : L)' / L;
    subplot(4, 1, 1);
    S = abs(fft(s) / L);
    S = S(1 : L / 2 + 1);
    S(2 : end - 1) = 2 * S(2 : end - 1);
    plot(fft_freq, S);
    ylabel('s(n)����Ƶ��');
    subplot(4, 1, 2);
    S_SYN = abs(fft(s_syn) / L);
    S_SYN = S_SYN(1 : L / 2 + 1);
    S_SYN(2 : end - 1) = 2 * S_SYN(2 : end - 1);
    plot(fft_freq, S_SYN);
    ylabel('s\_syn(n)����Ƶ��');
    subplot(4, 1, 3);
    S_SYN_V = abs(fft(s_syn_v) / L);
    S_SYN_V = S_SYN_V(1 : L + 1);
    S_SYN_V(2 : end - 1) = 2 * S_SYN_V(2 : end - 1);
    plot(fft_freq1, S_SYN_V);
    ylabel('s\_syn\_v(n)����Ƶ��');
    subplot(4, 1, 4);
    S_SYN_T = abs(fft(s_syn_t) / L);
    S_SYN_T = S_SYN_T(1 : L / 2 + 1);
    S_SYN_T(2 : end - 1) = 2 * S_SYN_T(2 : end - 1);
    plot(fft_freq, S_SYN_T);
    ylabel('s\_syn\_t(n)����Ƶ��');
    
    % ���������ļ�
    writespeech('.\save_files\exc.pcm',exc);
    writespeech('.\save_files\rec.pcm',s_rec);
    writespeech('.\save_files\exc_syn.pcm',exc_syn);
    writespeech('.\save_files\syn.pcm',s_syn);
    writespeech('.\save_files\exc_syn_t.pcm',exc_syn_t);
    writespeech('.\save_files\syn_t.pcm',s_syn_t);
    writespeech('.\save_files\exc_syn_v.pcm',exc_syn_v);
    writespeech('.\save_files\syn_v.pcm',s_syn_v);
return

% ��PCM�ļ��ж�������
function s = readspeech(filename, L)
    fid = fopen(filename, 'r');
    s = fread(fid, L, 'int16');
    fclose(fid);
return

% д������PCM�ļ���
function writespeech(filename,s)
    fid = fopen(filename,'w');
    fwrite(fid, s, 'int16');
    fclose(fid);
return

% ����һ�������Ļ������ڣ���Ҫ������
function PT = findpitch(s)
[B, A] = butter(5, 700/4000);
s = filter(B,A,s);
R = zeros(143,1);
for k=1:143
    R(k) = s(144:223)'*s(144-k:223-k);
end
[R1,T1] = max(R(80:143));
T1 = T1 + 79;
R1 = R1/(norm(s(144-T1:223-T1))+1);
[R2,T2] = max(R(40:79));
T2 = T2 + 39;
R2 = R2/(norm(s(144-T2:223-T2))+1);
[R3,T3] = max(R(20:39));
T3 = T3 + 19;
R3 = R3/(norm(s(144-T3:223-T3))+1);
Top = T1;
Rop = R1;
if R2 >= 0.85*Rop
    Rop = R2;
    Top = T2;
end
if R3 > 0.85*Rop
    Rop = R3;
    Top = T3;
end
PT = Top;
return