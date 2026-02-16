#define RCC_BASE (0x40023800)
#define GPIOB_BASE (0x40020400)
#define I2C_BASE (0x40005400)
#define TIME2_BASE (0x40000000)

#define RCC_AHB1ENR (*(volatile unsinged int *)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile unsinged int *)(RCC_BASE + 0x40))

#define GPIOB_MODER (*(volatile unsinged int *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER (*(volatile unsinged int *)(GPIOB_BASE + 0x04))
#define GPIOB_PUPDR (*(volatile unsinged int *)(GPIOB_BASE + 0x0C))
#define GPIOB_ODR (*(volatile unsinged int *)(GPIOB_BASE + 0x14))
#define GPIOB_AFRH (*(volatile unsinged int *)(GPIOB_BASE + 0x24))


#define I2C_CR1 (*(volatile unsinged int *)(I2C_BASE + 0x00))
#define I2C_CR2 (*(volatile unsinged int *)(I2C_BASE + 0x04))
#define I2C_DR (*(volatile unsinged int *)(I2C_BASE + 0x10))
#define I2C_SR1 (*(volatile unsinged int *)(I2C_BASE + 0x14))
#define I2C_SR2 (*(volatile unsinged int *)(I2C_BASE + 0x18))
#define I2C_CCR (*(volatile unsinged int *)(I2C_BASE + 0x1C))
#define i2C_TRISE (*(volatile unsinged int *)(I2C_BASE + 0x20))
void I2C_INIT();
void I2C_READ(int n , char* str);
int main(){
    I2C_INIT();
    char str[6];
    while(1){
        I2C_READ(6, str);
    }
}

I2C_INIT(){
    RCC_AHB1ENR |=(1<<1);

    GPIOB_MODER |=(1<<19);
    GPIOB_MODER &=~(1<<18);
    GPIOB_MODER |=(1<<17);
    GPIOB_MODER &=~(1<<16);

    GPIOB_OTYPER |=(1<<8);
    GPIOB_OTYPER |=(1<<9);

    GPIOB_PUPDR |=(1<<18);
    GPIOB_PUPDR &=~(1<<19);
    GPIOB_PUPDR |=(1<<16);
    GPIOB_PUPDR &=~(1<<17);   

    GPIOB_AFRH &=~(0xFF<<0);
    GPIOB_AFRH |= (1<<2);
    GPIOB_AFRH |=(1<<6);

    RCC_APB1ENR |=(1<<21);

    I2C_CR1 |=(1<<15);
    I2C_CR1 &=~(1<<15);

    I2C_CR2 |=(1<<4);

    I2C_CCR = 80 ;
    I2C_TRISE = 17;

    I2C_CR1 |=(1<<0);
}
void I2C_READ(int n, char* str){
    I2C_CR1 |=(1<<10);
    while(!(I2C_SR1 &(1<<1))){}
    (void)I2C_SR2;
    for(int i=0;i<n;i++){
        while(!(I2C_SR1 & (1<<6))){}
        srt[i]=I2C_DR;

    }
    I2C_CR1 &=~(1<<10);
}