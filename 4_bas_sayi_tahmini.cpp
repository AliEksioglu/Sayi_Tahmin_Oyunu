#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int toplameksi=0,toplamarti=0;
char sayilar[]={'0','1','2','3','4','5','6','7','8','9'};
char randomsayi[4];
struct top10{
	
	float  score;
	char isim[10];
	
};
struct top10 liste[10] , tutucu , oynayan;

int kontrol(char tahmin[]){ 
	
	for(int i=0;i<4;i++){
		for(int j=0;j<i;j++){
			if(tahmin[i]==tahmin[j]) return 0;
		}
	}
	
	return 1;
}

int karsilastir(char randomsayi[],char tahmin[]){
	
	int arti=0,eksi=0;
	for(int i=0;i<4;i++){         
		
		for(int j=0;j<4;j++){
			if(tahmin[i]==randomsayi[j] && i==j) arti++; 
			else if(tahmin[i]==randomsayi[j]) eksi++;	
		}
	}
	if(arti==4) {
		printf("\n%s -> -%d _ +%d ",tahmin,eksi,arti);
		toplamarti+=arti;
		return 1;
	}
	else if(arti>0 && eksi>0) printf("%s -> -%d _ +%d , yeri dogru %d tane rakam bildiniz - yeri yanlis %d tane rakam bildiniz \n",tahmin,eksi,arti,arti,eksi);
	else if(arti>0) printf("%s -> -%d _ +%d , yeri dogru %d adet rakam bildiniz\n",tahmin,eksi,arti,arti);
	else if(eksi>0)	printf("%s -> -%d _ +%d , yeri yanlis %d adet rakam bildiniz\n",tahmin,eksi,arti,eksi);
	else printf("%s -> -%d _ +%d , Bu rakamlardan hicbiri tutulan sayida yok\n",tahmin,eksi,arti);
	
	toplameksi+=eksi; 
	toplamarti+=arti;
	
	return 0;
}

float puanhesapla(int hak){
	
	float puan = (float)(10*toplamarti + 5*toplameksi + 1000/hak) - (float)(toplamarti * toplameksi)/(toplamarti+toplameksi);
	return puan;
}

void rastgeleSayi(){
	
	srand(time(NULL));
	
	for(int i=0;i<4;i++){
		
		int index=rand() % 9;
		randomsayi[i]=sayilar[index];
		
		for(int j=0;j<i;j++){
			if(randomsayi[i]==randomsayi[j]) {
				i=i-1; break;
			}
		}
	}
}

void listele(){	
for(int i=0;i<10;i++)
	{
		if(oynayan.score+0.1>liste[i].score)
		{		
			while(i<10){
				tutucu.score = liste[i].score;
				strcpy(tutucu.isim,liste[i].isim);
				
				liste[i].score = oynayan.score;
				strcpy(liste[i].isim,oynayan.isim);
				
				oynayan.score = tutucu.score;
				strcpy(oynayan.isim,tutucu.isim); 
				
				i++;
			}
			break;
		}
	}
	  
}


int main(){	
			
	char tahmin[4]; 
	int hak=10;
	float puan=0; 
	
	rastgeleSayi();
	printf("Random tutulan rakamlari farkli 4 basamakli sayi tahmin oyunu:(Bulmak icin 10 hakkiniz var)\n");
	
	while(hak>0)
	{	printf("\n random tutulan sayi: %s \n",randomsayi);
		printf("\nTahmininizi giriniz:",liste[5].score,liste[1].isim); scanf("%s",tahmin);	
		int sayac=0;
		for(int i=0;tahmin[i]!=NULL;i++) sayac++;    
		
		if(sayac!=4) {
			system("CLS");
			printf("\n4 basamakli bir sayi giriniz !!");
			continue;
		}
		else {
			if(kontrol(tahmin)==1) {
				if(karsilastir(randomsayi,tahmin)==1)
				{ 
					puan = puanhesapla(11-hak);
					printf(",Tebrikler rasgele tutulan sayiyi %d denemede bildiniz puaniniz: %.1f \n",11-hak,puan);
					int cevap;
					printf("Adiniz: "); scanf("%s",oynayan.isim); oynayan.score=puan;
					printf("(Tekrar oynamak icin 1 e basiniz)"); scanf("%d",&cevap);	
					if(cevap==1)
					{
						toplameksi=0,toplamarti=0;
						hak=10;
						rastgeleSayi();
						listele();
						system("CLS");
						continue;
					}
					else {
						listele();
						system("CLS");
						break;
					}
				}
			}
			else if(kontrol(tahmin)==0){
				printf("Rakamlari farkli 4 basamakli bir sayi giriniz..\n");
				continue;
			}
		}
		
		hak--;
		
		if(hak==0) {
			printf("\n%s -> random tutulan sayi buydu 10 denemede de bulamadiniz.. puaniniz = 0 \n",randomsayi);
			printf("Adiniz: "); 
			scanf("%s",oynayan.isim); oynayan.score=0;
			int cevap = 0;
			printf("(Tekrar oynamak icin 1 e basiniz)"); scanf("%d",&cevap);
			if(cevap==1){
				toplameksi=0,toplamarti=0;
				hak=10;
				rastgeleSayi();
				listele();
				system("CLS");
				continue;
			}
			else {
				listele();
				system("CLS");
				break;
			}
		}
		printf("\n**Bulmak icin %d Hakkiniz kaldi**",hak);
		
	}
	printf("   isim     -    puan\n");
	for(int i = 0;i<10;i++) printf("%d.  %s    -    %.1f \n",i+1,liste[i].isim,liste[i].score);
	
	
	return 0;
}
