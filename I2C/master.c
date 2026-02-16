#define RCC_BASE (0x40023800)
#define GPIOA_BASE (0x40020000)
#define GPIOB_BASE (0x40020400)
#define I2C_BASE (0x40005400)
#define TIM2_BASE (0x40000000)

#define RCC_AHB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x40))

#define GPIOA_MODER (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOA_OTYPER (*(volatile unsigned int *)(GPIOB_BASE + 0x04))
#define GPIOA_PUPDR (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOA_ODR (*(volatile unsigned int *)(GPIOB_BASE + 0x14))
#define GPIOA_AFRH (*(volatile unsigned int *)(GPIOB_BASE + 0x24))

#define GPIOB_MODER (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER (*(volatile unsigned int *)(GPIOB_BASE + 0x04))
#define GPIOB_PUPDR (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOB_ODR (*(volatile unsigned int *)(GPIOB_BASE + 0x14))
#define GPIOB_AFRH (*(volatile unsigned int *)(GPIOB_BASE + 0x24))

#define I2C_CR1 (*(volatile unsigned int *)(I2C_BASE + 0x00))
#define I2C_CR2 (*(volatile unsigned int *)(I2C_BASE + 0x04))
#define I2C_DR (*(volatile unsigned int *)(I2C_BASE + 0x10))
#define I2C_SR1 (*(volatile unsigned int *)(I2C_BASE + 0x14))
#define I2C_SR2 (*(volatile unsigned int *)(I2C_BASE + 0x14))
#define I2C_CCR (*(volatile unsigned int *)(I2C_BASE + 0x1C))
#define I2C_TRISE (*(volatile unsigned int *)(I2C_BASE + 0x20))
void I2C_INIT();
void I2C_SEND(char saddr,int n,char* str)

int main(){
    I2C_INIT();
    while(1){
        I2C_SEND(0x12,6,"CSE-RU");
    }
}
void I2C_INIT(){
    RCC_AHB1ENR |=(1<<1);

    GPIOA_MODER |=(1<<19);
    GPIOA_MODER &=~(1<<18);
    GPIOA_MODER |=(1<<17);
    GPIOA_MODER &=~(1<<16);

    GPIOB_OTYPER |=(1<<8);
    GPIOB_OTYPER |=(1<<9);

    GPIOB_PUPDR |=(1<<18);
    GPIOB_PUPDR &=~(1<<19);
    GPIOB_PUPDR |=(1<<16);
    GPIOB_PUPDR &=~(1<<17);

    GPIOB_AFRH &=~(0xFF<<0);
    GPIOB_AFRH |=(1<<2);
    GPIOB_AFRH |=(1<<6);
    RCC_APB1ENR |=(1<<21);

    I2C_CR1 |=(1<<15);
    I2C_CR1 &=~(1<<15);

    I2C_CR2 |=(1<<4);
    I2C_CCR =80;
    I2C_TRISE=17;

    I2C_CR1 |=(1<<0);
}

void I2C_SEND(char saddr,int n,char* str){
    while(I2C_SR2 & (1<<1)){}

    I2C_CR1 |=(1<<8);
    while(!(I2C_SR1&(1<<0))){}

    I2C_DR = (saddr<<1);
    while(!(I2C_SR1&(1<<1))){}

    for(int i=0;i<n;i++){
        while(!(I2C_SR1&(1<<7))){}
        I2C_DE = *str++;
    }
    while(!(I2C_SR1 & (1<<2))){}

    I2C_CR1 |= (1<<9);

}