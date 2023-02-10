import { PrismaClient } from '@prisma/client'
import express from 'express'
const prisma = new PrismaClient()

const app = express()

async function main() {
  console.log('running')
  app.listen(3000, () =>
    console.log('🚀 Server ready at: http://localhost:3000')
  )
}

main()
  .catch((e) => console.error(e))
  .finally(async () => await prisma.$disconnect())
